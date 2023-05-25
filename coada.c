#include <stdio.h>
#include <stdlib.h>

#include "macrouri.h"
#include "byte_string.h"
#include "coada.h"

NodCoada *CreareNodCoada(char *informatie)
{
    // cream un nou nod
    NodCoada* nod_nou = malloc(sizeof(NodCoada));
    nod_nou->informatie = (char *)malloc(LUNGIME_LINII * sizeof(char));
    nod_nou -> urm = nod_nou -> pred = NULL;
    byteop_strcpy(nod_nou -> informatie, informatie);
    return nod_nou;
}

Coada* CreareCoada(void)
{
	// cream o Coada noua
	Coada* coada_noua = malloc(sizeof(Coada));
	coada_noua -> inceput = NULL;
	coada_noua -> final = NULL;
	return coada_noua;
}

void CoadaInserareFinal(Coada* coada_input, char *informatie)
{
    if (coada_input == NULL) {
        // Coada este vida
        coada_input = CreareCoada();
        coada_input->inceput =  coada_input->final = CreareNodCoada(informatie);
        return;
    } 
    if (coada_input != NULL && coada_input->inceput == NULL) {
        // Coada nu este initializata, ea exista, dar nu retine nimic
        coada_input->inceput = coada_input->final = CreareNodCoada(informatie);
        return;
    }
    // Coada are cel putin un element
    NodCoada* new_nod = CreareNodCoada(informatie);
    new_nod->pred = coada_input->final;
    coada_input->final->urm = new_nod;
    coada_input->final = new_nod;
    return ;
}


void CoadaDeleteFirstNode(Coada* coada_input)
{
    // sterge orimul element al listei , dar nu si Coada
    NodCoada* stergator = coada_input -> inceput;
    coada_input -> inceput = coada_input -> inceput -> urm;
    if (coada_input -> inceput != NULL) {
        coada_input -> inceput -> pred = NULL;
    }
    free(stergator->informatie);
    free(stergator);
    return ;

}

void CoadaFullDelete(Coada* coada_input)
{
	// Guard against young player errors
	if (coada_input == NULL) {
        free(coada_input);
        return ;
    }
	while (coada_input -> inceput != NULL) {
		// stergem succeiv primul element al listei
		// o privim practic asemenea unei cozis
        // stergere de la inceput
		CoadaDeleteFirstNode(coada_input);
	}

	free(coada_input);
	return ;
}
