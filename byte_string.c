/* TRIFAN BOGDAN-CRISTIAN , 312CD */
/* PROIECT PCLP 3 */
#include <stdio.h>
#include "byte_string.h"
#include "macrouri.h"

int byteop_strlen(char *sir)
{
    char* ptr = sir;
    while (*ptr)
        ++ptr;
    return ptr - sir;
}

void StringPrintFile(FILE *fout, char* str)
{
    while (*str) {
        fprintf(fout, "%c", *str);
        str++;
    }
}

int byteop_strcmp(char* sir_unu, char* sir_doi)
{
    while (*sir_unu && (*sir_unu & *sir_doi)) {
        sir_unu++;
        sir_doi++;
    }

    // aici facem diferenta dintre caracterle ASCII
    // ale primelor caractere distincte din siruri, luate de la dreapta la stanga
    return *(unsigned char*)sir_unu - *(unsigned char*)sir_doi;
}

void byteop_strcpy(char* destinatie, char* sursa)
{
    while (*sursa) {
        *destinatie = *sursa;
        destinatie++;
        sursa++;
    }
    
    *destinatie = '\0';  // adaugam NULL la final
}

void byteop_strcat(char* destinatie, char* sursa)
{
    while (*destinatie) {
        destinatie++;
    }
    
    while (*sursa) {
        *destinatie = *sursa;
        destinatie++;
        sursa++;
    }
    
    *destinatie = '\0';  // adaugam NULL la final
}

char *byteop_strstr(char *destinatie, char *sursa) 
{
    while (*destinatie) {
        char* d = destinatie;
        char* s = sursa;
        
        while (*d && *s && (*d == *s)) {
            d++;
            s++;
        }
        
        if (!*s) {
            return (char*)destinatie;
        }
        
        destinatie++;
    }
    
    return NULL;
}

char *byteop_strtok(char* str, char* sep)
{
    static char* buffer = NULL;

    if (str)
        buffer = str;

    if (!buffer)
        return NULL;

    char* token = buffer;
    
    while (*buffer) {
        int issep = 0;
        
        char *d = sep;
        while (*d) {
            if (*buffer == *d) {
                issep = 1;
                break;
            }
            d++;
        }
        
        if (issep) {
            *buffer = '\0';
            buffer++;
            return token;
        }

        buffer++;
    }

    buffer = NULL;

    return token;
}
