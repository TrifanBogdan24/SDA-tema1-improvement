/* TRIFAN BOGDAN-CRISTIAN , 312CD */
/* PROIECT PCLP 3 */
#ifndef _COADA_H_
#define _COADA_H_

typedef struct NodCoada {
    char *informatie;
    struct NodCoada* urm;    // adresa catre urmatorul nod din Coada
    struct NodCoada* pred;   // adresa catre nodul anterior din Coada
} NodCoada;


typedef struct Coada {
    NodCoada* inceput;       // va memora nodul de inceput al listei
    NodCoada* final;         // va memora nodul final al listei

} Coada;

NodCoada *CreareNodCoada(char *informatie);

Coada* CreareCoada(void);

void CoadaInserareFinal(Coada* coada_input, char *informatie);

void CoadaDeleteFirstNode(Coada* coada_input);

void CoadaFullDelete(Coada* coada_input);

#endif
