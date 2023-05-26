/* TRIFAN BOGDAN-CRISTIAN , 312CD */
/* PROIECT PCLP 3 */
#include <stdio.h>
#include <stdlib.h>

#include "../macrouri.h"
#include "../byte_string.h"
#include "liner.h"

int is_c_file(char *name_of_file)
{
    if (!byteop_strstr(name_of_file, ".c") && !byteop_strstr(name_of_file, ".h"))
        return ZERO;

    return UNU;
}

void file_opener(char const *name_of_file)
{
    printf("Checking file %s\n", name_of_file);
    FILE *fin = fopen(name_of_file, "rt");
    if (!fin) {
        fclose(fin);
        printf("\033[0mEroare la deschiderea fisierului.\033[0m\n");
        return;
    }

    char *name = (char *)name_of_file;
    if (!is_c_file(name)) {
        fclose(fin);
        printf("\033[0mFisierul %s nu este fisier C!\033[0m\n", name_of_file);
        return;
    }

    char **txt = (char **)malloc(MAX_LIN * sizeof(char *));
    int mistakes = ZERO;
    for (int i = ZERO; i < MAX_LIN; i++) {
        txt[i] = (char *)malloc(MAX_COL * sizeof(char));
        byteop_strcpy(txt[i], "init");
    }

    int nr_lines = ZERO;
    while (!feof(fin)) {
        fgets(txt[nr_lines], MAX_COL, fin);
        nr_lines++;
        if (nr_lines == MAX_LIN) {
            printf("\033[0mFisierul are prea multe linii pentru ca checkerul");
            printf("\033[0m sa le verifice pe toate.\033[0m\n");
            break;
        }
    }

    int i = ZERO;
    while (i < nr_lines) {

        i = multiple_blank_lines(name_of_file, txt, nr_lines, i, &mistakes);
        trailing_whitespace(name_of_file, txt, nr_lines, i, &mistakes);
        long_line(name_of_file, txt, nr_lines, i, &mistakes);
        comma(name_of_file, txt, nr_lines, i, &mistakes);
        space_bracket(name_of_file, txt, nr_lines, i, &mistakes);
        punct_si_virgula(name_of_file, txt, nr_lines, i, &mistakes);
        verify_for(name_of_file, txt, nr_lines, i, &mistakes);
        verify_if(name_of_file, txt, nr_lines, i, &mistakes);
        verify_while_simplu(name_of_file, txt, nr_lines, i, &mistakes);
        verify_do_from_do_while(name_of_file, txt, nr_lines, i, &mistakes);
        //verify_if(name_of_file, txt, nr_lines, i, &mistakes);
        non_equal_zero(name_of_file, txt, nr_lines, i, &mistakes);
        equal_zero(name_of_file, txt, nr_lines, i, &mistakes);
        non_equal_null(name_of_file, txt, nr_lines, i, &mistakes);
        equal_null(name_of_file, txt, nr_lines, i, &mistakes);

        i++;
    }

    if (byteop_strlen(txt[nr_lines - UNU])) {
        printf("\033[31m%s : ERROR : \033[0m", name_of_file);
        printf("\033[31mexpected new-line character at the end of the file.\033[0m\n"); 
        mistakes++;
    }

    if (!mistakes) {
        printf("\033[32%s : seems ok, \033[0m", name_of_file);
        printf("\033[32but should also be checked manually. Good luck!\033[0m\n");
    } else {
        printf("\033[33mIn the file %s have been identified\033[0m", name_of_file);
        printf("\033[33m %d coding style errors.\033[0m\n\n", mistakes);
    }

    for (int i = ZERO; i < MAX_LIN; i++)
        free(txt[i]);
    free(txt);
    fclose(fin);
}

int main(int argc, char const *argv[])
{
    // primul parametru este executabili, indexat de la 0
    for (int i = UNU; i < argc; i++)
        file_opener(argv[i]);

    return 0;
}
