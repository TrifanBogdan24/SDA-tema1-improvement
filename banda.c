/* TRIFAN BOGDAN-CRISTIAN , 312CD */
/* PROIECT PCLP 3 */
#include <stdio.h>
#include <stdlib.h>

#include "macrouri.h"
#include "byte_string.h"
#include "banda.h"

NodBanda *CreareNodBanda(char caracter)
{
    // cream un nou nod
    NodBanda* nod_nou = malloc(sizeof(NodBanda));
   
    nod_nou -> urm = nod_nou -> pred = NULL;
    nod_nou -> caracter = caracter;
    return nod_nou;
}


LBanda* CreareBanda(void)
{
    // creem o banda cu santinela
    LBanda* banda_noua = malloc(sizeof(LBanda));
    banda_noua->inceput = banda_noua->final = banda_noua->deget = CreareNodBanda(DIEZ);
    banda_noua->santinela = CreareNodBanda(SPACE);
    banda_noua->santinela->urm = banda_noua->inceput;
    banda_noua->inceput->pred = banda_noua->santinela;
    return banda_noua;
}


void BandaStergere(LBanda* banda_input)
{
    while (banda_input->final != banda_input->santinela) {
        NodBanda* stergator = banda_input->final;
        banda_input->final = banda_input->final->pred;
        free(stergator);
    }
    free(banda_input->santinela);
    free(banda_input);
}


void BandaInserareFinal(LBanda* banda_input ,char caracter)
{
    
    if (banda_input == NULL || banda_input->inceput == NULL) {
        // Coada vida , elementul va deveni primul nod al listei
        banda_input -> inceput = banda_input -> final = CreareNodBanda(caracter);
        banda_input->santinela->urm = banda_input->inceput;
        banda_input->inceput->pred = banda_input->santinela;
        return;
    }
    
    // Coada  cel putin un element
    NodBanda* nodul_final = CreareNodBanda(caracter);
    nodul_final -> pred = banda_input -> final;
    banda_input -> final -> urm = nodul_final;
    banda_input -> final = nodul_final;

    return ;
   
}


void BandaInserareStanga(FILE* fout , LBanda *banda_input , char caracter)
{
    // inseram in stanga santinelei
    if (banda_input->deget == banda_input->inceput) {
        // inceput de banda

        StringPrintFile(fout, EROARE);
        StringPrintFile(fout, "\n");
        return;
    } else {
        NodBanda* nod_inserare_st = CreareNodBanda(caracter);
        nod_inserare_st->pred = banda_input->deget->pred;
        nod_inserare_st->urm = banda_input->deget;
        banda_input->deget->pred->urm = nod_inserare_st;
        banda_input->deget->pred = nod_inserare_st;
        banda_input->deget = nod_inserare_st;
        return;
    }
}


void BandaInserareDreapta(LBanda *banda_input , char caracter)
{
    // inseram in dreapta santinelei
    if (banda_input->deget == banda_input->final) {
        // inseram la final
        BandaInserareFinal(banda_input , caracter);
        banda_input->deget = banda_input->final; 
        // printf("%s\n" , banda_input->deget->informatie);
        return;
    }
    
    NodBanda* nod_inserare_dr = CreareNodBanda(caracter);
    nod_inserare_dr->pred = banda_input->deget;
    nod_inserare_dr->urm = banda_input->deget->urm;
    banda_input->deget->urm->pred = nod_inserare_dr;
    banda_input->deget->urm = nod_inserare_dr;
    banda_input->deget = nod_inserare_dr;
}


void display(FILE* fout , LBanda *banda_input)
{
    NodBanda* parcurgere = banda_input -> inceput;
    while (parcurgere != NULL) {
        if (parcurgere == banda_input -> deget) {
            fprintf(fout , "|%c|" , parcurgere -> caracter);
        } else {
            fprintf(fout , "%c" , parcurgere -> caracter);
        }
        parcurgere = parcurgere -> urm;
    }
    fprintf(fout , "\n");
    return ;
}
