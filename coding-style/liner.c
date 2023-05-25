/* TRIFAN BOGDAN-CRISTIAN , 312CD */
/* PROIECT PCLP 3 */
#include <stdio.h>
#include "../macrouri.h"
#include "../byte_string.h"
#include "liner.h"

#define NON_BLANK(c) ((c) ^ '\n') && ((c) ^ ' ')
#define CHAR_EGAL(c1, c2) ((c1) ^ (c2) ? 0 : 1)
#define ESTE_CIFRA(c) (('0' <= (c)) && ((c) <= '9') ? 1 : 0)
#define ESTE_LITERA(c) ((('a' <= (c) && (c) <= 'z') || ('A' <= (c) && (c) <= 'Z')) ? 1 : 0)

int blank_line(char *sir)
{
    for (int i = ZERO; i < byteop_strlen(sir); i++) {
        if (NON_BLANK(sir[i]))
            return ZERO; // linia nu este de tip blank-line
    }
    return UNU;  // linie de tip blank-line
}

int multiple_blank_lines(char const *f_name, char **txt, int nr_lines, int i, int *error)
{
    int j = i;
    // int lungime = byteop_strlen(txt[j]);
    while (j < nr_lines && blank_line(txt[j]))
        j++;


    if (j > i + UNU) {
        printf("%s : ERROR : ", f_name);
        printf("multiple blank-lines from %d to %d\n", i + UNU, j);
        (*error)++;
    }
    return j;
}

void long_line(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    int lungime = byteop_strlen(txt[lin]);
    if (lungime > OPT_ZECI) {
        printf("%s : ERROR : ", f_name);
        printf("line %d : has a length of %d, ", lin + UNU, lungime);
        printf("bigger than %d.\n", OPT_ZECI);
        (*error)++;
    }
}

void comma(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    int good = UNU; // nu verificam in interiorul ghilimelelor
    int lungime = byteop_strlen(txt[lin]);
    for (int i = ZERO; i < lungime; i++) {
        if (CHAR_EGAL(txt[lin][i], '"'))
            good = UNU - good;

        if (txt[lin][i] == ',' && good) {
            if (i > ZERO && CHAR_EGAL(txt[lin][i - UNU], ' ')) {
                printf("%s : ERROR : ", f_name);
                printf("line %d, column %i :", lin + UNU, i + UNU);
                printf(" there should be no space(s) before a comma ','.\n");
                (*error)++;
            } 

            if (i < lungime - UNU && !CHAR_EGAL(txt[lin][i + UNU] ,' ')) {
                printf("%s : ERROR : ", f_name);
                printf("line %d, column %i :", lin + UNU, i + DOI);
                printf(" expected a space ' ' after a comma ','.\n");
                (*error)++;
            }

            int j = i + UNU;
            while (j < lungime && CHAR_EGAL(txt[lin][j], ' '))
                j++;

            if (j > i + DOI) {
                printf("%s : ERROR : ", f_name);
                printf("line %d, column %d :", lin + UNU, i + UNU);
                printf(" too many spaces after the comma.\n");
                (*error)++;
            }
        }
    }
}

void trailing_whitespace(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    int lungime = byteop_strlen(txt[lin]);
    if (lungime - UNU > ZERO && CHAR_EGAL(txt[lin][lungime- DOI], ' ')) {
        // daca col = 0, atunci blank line, care este deja verificat
        printf("%s : ERROR : ", f_name);
        printf("line %d : trailing whitespaces", lin + UNU);
        printf(" at the end of the line.\n");
        (*error)++;
    }
}

void space_bracket(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    int lungime = byteop_strlen(txt[lin]);
    int good = UNU; // nu o sa facem verificari intre ghilimele si comentarii

    if (byteop_strstr(txt[lin], "{") && byteop_strstr(txt[lin], "}")) {
        printf("%s : ERROR : ", f_name);
        printf(" line %d : is not a good practice ", lin + UNU);
        printf("to have two braces one the same line '{...}.'.\n");
        (*error)++;
    }

    for (int i = ZERO; i < lungime; i++) {
        if (txt[lin][i] == '"')
            good = UNU - good;

        if (CHAR_EGAL(txt[lin][i], '/') && i <= lungime - DOI && 
            (CHAR_EGAL(txt[lin][i + 1], '/') || CHAR_EGAL(txt[lin][i + 1], '*')))
            good = ZERO;

        if (!good)
            continue;

        if (CHAR_EGAL(txt[lin][i], '(') && i < lungime
            && CHAR_EGAL(txt[lin][i + UNU], ' ')) {
            printf("%s : ERROR : ", f_name);
            printf("line %d, column %d :", lin + UNU, i + UNU);
            printf(" unneccesary space(s) after round bracket '('.\n");
            (*error)++;
            continue;
        }

        if (CHAR_EGAL(txt[lin][i], '[') && i < lungime
            && CHAR_EGAL(txt[lin][i + UNU], ' ')) {
            printf("%s : ERROR : ", f_name);
            printf("line %d, column %d :", lin + UNU, i + UNU);
            printf(" unneccesary space(s) after square bracket '['.\n");
            (*error)++;
            continue;
        }

        if (CHAR_EGAL(txt[lin][i], ')') && i > ZERO &&
            CHAR_EGAL(txt[lin][i - UNU], ' ') && byteop_strstr(txt[lin], "{")) {
            printf("%s : ERROR : ", f_name);
            printf("line %d, column %d :", lin + UNU, i + UNU);
            printf(" unneccesary space(s) before round bracket ')'.\n");
            (*error)++;
            continue;
        }

        if (txt[lin][i] == ']' && i > ZERO && txt[lin][i - UNU] == ' ' &&
            byteop_strstr(txt[lin], "{")) {
            printf("%s : ERROR : ", f_name);
            printf("line %d, column %d :", lin + UNU, i + UNU);
            printf(" unneccesary space(s) before square bracket ']'.\n");
            (*error)++;
            continue;
        }
    }
}

int for_declaration(char **txt, int nr_line, int lin)
{
    // daca expresia for se intinde pe mai multe randuri
    // functia nu mia functioneaza
    if (byteop_strstr(txt[lin], "for"))
        return UNU;

    return ZERO;
}

int is_some_cmd_in_right(char **txt, int nr_lines, int lin, int col)
{   
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    int lungime = byteop_strlen(txt[lin]);
    
    while (col < lungime && CHAR_EGAL(txt[lin][col], ' ')) 
        col++;
    
    if (col == lungime)
        return UNU;

    if (ESTE_LITERA(txt[lin][col]))
        return UNU;
    return ZERO;
}

void punct_si_virgula(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    int lungime = byteop_strlen(txt[lin]);
    for (int i = ZERO; i < lungime; i++) {
        if (!CHAR_EGAL(txt[lin][i], ';'))
            continue;

        if (i > ZERO && CHAR_EGAL(txt[lin][i - UNU], ' ')) {
            printf("%s : ERROR :", f_name);
            printf("line %d, column %d : ", lin + UNU, i + UNU);
            printf(" unneccesary space(s) before ';'.\n");
            (*error)++;
        }

        // aici vreua sa verific daca sunt mai multe operatii desp. prin ;
        // if (!for_declaration(txt, lin, i) ||
        //     is_some_cmd_in_right(txt, nr_lines, lin, i)) {
        //     printf("%s : ERROR ", f_name);
        //     printf(" linia %d", lin + UNU);
        //     printf(" bad practice to separate multiple operations by ';'.\n");
        //     (*error)++;
        // }
    }
}

void verify_for(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    char *p = byteop_strstr(txt[lin], "for");
    if (!p)
        return;

    p += byteop_strlen("for");
    if (*p != ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : there should be a space ", lin + UNU);
        printf("between 'for' and paranthesis '('.\n");
        (*error)++;
    }

    p += UNU;
    if (*p && *p == ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : too many spaces ", lin + UNU);
        printf("between 'for' and paranthesis '('.\n");
        (*error)++;
    }

}

void verify_if(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    char *p = byteop_strstr(txt[lin], "if");
    if (!p)
        return;

    p += byteop_strlen("if");
    if (*p && *p != ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : there should be a space ", lin + UNU);
        printf("between 'if' and paranthesis '('.\n");
        (*error)++;
    }

    p += UNU;
    if (*p == ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : too many spaces ", lin + UNU);
        printf("between 'if' and paranthesis '('.\n");
        (*error)++;
    }

}

void verify_while_simplu(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{   
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    char *p = byteop_strstr(txt[lin], "while");
    if (!p)
        return;

    if (byteop_strstr(txt[lin], "}"))
        return;

    p += byteop_strlen("while");
    if (*p && *p != ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : there should be a space ", lin + UNU);
        printf("between 'while' and paranthesis '('.\n");
        (*error)++;
    }

    p += UNU;
    if (*p == ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : too many spaces ", lin + UNU);
        printf("between 'while' and paranthesis '('.\n");
        (*error)++;
    }

}

void verify_do_from_do_while(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    char *p = byteop_strstr(txt[lin], "do");
    if (!p)
        return;
    p += byteop_strlen("do");

    if (!byteop_strstr(txt[lin], "{")) {
        printf("%s : ERROR : ", f_name);
        printf("line %d : bracket '{' should ", lin + UNU);
        printf("be on the same line with 'while'.\n");
        (*error)++;
    }

    if (*p && *p != ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : there should be a space ", lin + UNU);
        printf("between 'do' and bracket '{'.\n");
        (*error)++;
    }

    p += UNU;
    if (*p == ' ') {
        printf("%s : ERROR : ", f_name);
        printf("line %d : too many spaces ", lin + UNU);
        printf("between 'while' and bracket '{'.\n");
        (*error)++;
    }
}

void non_equal_zero(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    if (byteop_strstr(txt[lin], "!= 0") || byteop_strstr(txt[lin], "!=0")) {
        printf("%s : ERROR : ", f_name);
        printf("line %d : verification with 0 ", lin + UNU);
        printf("can be eliminated. Keep only the expresion and the ");
        printf("compiler will check if it's a non-zero value.\n");
        (*error)++;
    }
}

void equal_zero(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    if (byteop_strstr(txt[lin], "== 0") || byteop_strstr(txt[lin], "==0")) {
        printf("%s : ERROR : ", f_name);
        printf("line %d : verification with 0 ", lin + UNU);
        printf("can be eliminated. Keep only the expresion, with a '!' in front");
        printf(", and the compiler will check if it's zero.\n");
        (*error)++;
    }
}

void non_equal_null(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{    
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    if (byteop_strstr(txt[lin], "!= NULL") || byteop_strstr(txt[lin], "!=NULL")) {
        printf("%s : ERROR : ", f_name);
        printf("line %d : verification with NULL ", lin + UNU);
        printf("can be eliminated. Keep only the expresion and the ");
        printf("compiler will check if it's a non-null value.\n");
        (*error)++;
    }
}

void equal_null(char const *f_name, char **txt, int nr_lines, int lin, int *error)
{    
    if (lin >= nr_lines)
        return;

    if (!txt[lin])
        return;

    if (byteop_strstr(txt[lin], "== NULL") || byteop_strstr(txt[lin], "==NULL")) {
        printf("%s : ERROR : ", f_name);
        printf("line %d : verification with NULL ", lin + UNU);
        printf("can be eliminated. Keep only the expresion, with a '!' in front");
        printf(", and the compiler will check if it's null.\n");
        (*error)++;
    }
}
