/* TRIFAN BOGDAN-CRISTIAN , 312CD */
/* PROIECT PCLP 3 */
#ifndef _BANDA_H_
#define _BANDA_H_

typedef struct NodBanda {
    char caracter;
    struct NodBanda* urm;    // adresa catre urmatorul nod din Coada
    struct NodBanda* pred;   // adresa catre nodul anterior din Coada
} NodBanda;


typedef struct LBanda{
    NodBanda* inceput;       // va memora nodul de inceput al listei
    NodBanda* final;         // va memora nodul final al listei
    NodBanda* santinela;    // santinela, fundatia listei
    NodBanda* deget;         // va memora nodul catre care degetul indica
} LBanda;

NodBanda *CreareNodBanda(char caracter);

LBanda* CreareBanda(void);

void BandaStergere(LBanda* banda_input);

void BandaInserareFinal(LBanda* banda_input ,char caracter);

void BandaInserareStanga(FILE* fout , LBanda *banda_input , char caracter);

void BandaInserareDreapta(LBanda *banda_input , char caracter);

void display(FILE* fout , LBanda *banda_input);


#endif
