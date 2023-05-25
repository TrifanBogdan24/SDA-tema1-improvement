#include <stdio.h>
#include <stdlib.h>

#include "stiva.h"
#include "banda.h"

void StivaPush(SStiva *stiva_input, NodBanda* varf_nou)
{
    SStiva stiva_noua = (SStiva) malloc(sizeof(NodStiva));
    stiva_noua -> informatie = varf_nou;
    stiva_noua->urm = *stiva_input;
    *stiva_input = stiva_noua;
    return ; 
}
    

void StivaPop(SStiva* stiva_input)
{
    if (stiva_input != NULL) {
        SStiva stergator = *stiva_input;
        *stiva_input = (*stiva_input)->urm;
        free(stergator);
    }

}


void DeleteStiva(SStiva* stiva_input)
{
    while (*stiva_input != NULL) {
        StivaPop(stiva_input);
    }
    free(stiva_input);
    return;
}
