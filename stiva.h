/* TRIFAN BOGDAN-CRISTIAN , 312CD */
/* PROIECT PCLP 3 */
#ifndef _STIVA_H_
#define _STIVA_H_

#include "banda.h"

typedef struct Stiva {
    struct Stiva* urm;
    NodBanda* informatie;
} NodStiva, *SStiva;

void StivaPush(SStiva *stiva_input, NodBanda* varf_nou);

void StivaPop(SStiva* stiva_input);

void DeleteStiva(SStiva* stiva_input);

#endif
