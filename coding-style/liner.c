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
    if (i >= nr_lines)
        return i;

    if (!txt[i])
        return i;

    int j = i;
    // int lungime = byteop_strlen(txt[j]);
    while (j < nr_lines && blank_line(txt[j]))
        j++;


    if (j > i + UNU) {
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mmultiple blank-lines from %d to %d.\033[0m\n", i + UNU, j);
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
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : has a length of %d, \033[0m", lin + UNU, lungime);
        printf("\033[31mbbigger than %d.\033[0m\n", OPT_ZECI);
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
                printf("\033[31m%s : ERROR : \033[0m", f_name);
                printf("\033[31mline %d, column %i :\033[0m", lin + UNU, i + UNU);
                printf("\033[31m there should be no space(s) before a comma ','.\033[0m\n");
                (*error)++;
            } 

            if (i < lungime - UNU && !CHAR_EGAL(txt[lin][i + UNU] ,' ')) {
                printf("\033[31m%s : ERROR : ", f_name);
                printf("\033[31mline %d, column %i :", lin + UNU, i + DOI);
                printf("\033[31m expected a space ' ' after a comma ','.\033[0m\n");
                (*error)++;
            }

            int j = i + UNU;
            while (j < lungime && CHAR_EGAL(txt[lin][j], ' '))
                j++;

            if (j > i + DOI) {
                printf("\033[31m%s : ERROR : \033[0m", f_name);
                printf("\033[31mline %d, column %d :\033[0m", lin + UNU, i + UNU);
                printf("\033[31m too many spaces after the comma.\033[0m\n");
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
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : trailing whitespaces\033[0m", lin + UNU);
        printf("\033[31m at the end of the line.\033[0m\n");
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
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31m line %d : is not a good practice \033[0m", lin + UNU);
        printf("\033[31mto have two braces one the same line '{...}.'.\033[0m\n");
        (*error)++;
    }

    for (int i = ZERO; i < lungime; i++) {
        if (CHAR_EGAL(txt[lin][i], '"'))
            good = UNU - good;

        if (CHAR_EGAL(txt[lin][i], '/') && i <= lungime - DOI && 
            (CHAR_EGAL(txt[lin][i + 1], '/') || CHAR_EGAL(txt[lin][i + 1], '*')))
            good = ZERO;

        if (!good)
            continue;

        if (CHAR_EGAL(txt[lin][i], '(') && i < lungime
            && CHAR_EGAL(txt[lin][i + UNU], ' ')) {
            printf("\033[31m%s : ERROR : \033[0m", f_name);
            printf("\033[31mline %d, column %d :\033[0m", lin + UNU, i + UNU);
            printf("\033[31m unneccesary space(s) after round bracket '('.\033[0m\n");
            (*error)++;
            continue;
        }

        if (CHAR_EGAL(txt[lin][i], '[') && i < lungime
            && CHAR_EGAL(txt[lin][i + UNU], ' ')) {
            printf("\033[31m%s : ERROR : \033[0m", f_name);
            printf("\033[31mline %d, column %d :\033[0m", lin + UNU, i + UNU);
            printf("\033[31m unneccesary space(s) after square bracket '['.\033[0m\n");
            (*error)++;
            continue;
        }

        if (CHAR_EGAL(txt[lin][i], ')') && i > ZERO &&
            CHAR_EGAL(txt[lin][i - UNU], ' ') && byteop_strstr(txt[lin], "{")) {
            printf("\033[31m%s : ERROR : \033[0m", f_name);
            printf("\033[31mline %d, column %d :\033[0m", lin + UNU, i + UNU);
            printf("\033[31m unneccesary space(s) before round bracket ')'.\033[0m\n");
            (*error)++;
            continue;
        }

        if (txt[lin][i] == ']' && i > ZERO && txt[lin][i - UNU] == ' ' &&
            byteop_strstr(txt[lin], "{")) {
            printf("\033[31m%s : ERROR : \033[0m", f_name);
            printf("\033[31mline %d, column %d :\033[0m", lin + UNU, i + UNU);
            printf("\033[31m unneccesary space(s) before square bracket ']'.\033[0m\n");
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
        return lin;

    if (!txt[lin])
        return lin;

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
            printf("\033[31m%s : ERROR : \033[0m", f_name);
            printf("\033[31mline %d, column %d : \033[0m", lin + UNU, i + UNU);
            printf("\033[31m unneccesary space(s) before ';'.\033[0m\n");
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
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : there should be a space \033[0m", lin + UNU);
        printf("\033[31mbetween 'for' and paranthesis '('.\033[0m\n");
        (*error)++;
    }

    p += UNU;
    if (*p && *p == ' ') {
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : too many spaces \033[0m", lin + UNU);
        printf("\033[31mbetween 'for' and paranthesis '('.\033[0m\n");
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
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : there should be a space \033[0m", lin + UNU);
        printf("\033[31mbetween 'if' and paranthesis '('.\033[0m\n");
        (*error)++;
    }

    p += UNU;
    if (*p == ' ') {
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : too many spaces \033[0m", lin + UNU);
        printf("\033[31mbetween 'if' and paranthesis '('\033[0m.\n");
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
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : there should be a space \033[0m", lin + UNU);
        printf("\033[31mbetween 'while' and paranthesis '('.\033[0m\n");
        (*error)++;
    }

    p += UNU;
    if (*p == ' ') {
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : too many spaces \033[0m", lin + UNU);
        printf("\033[31mbetween 'while' and paranthesis '('.\033[0m\n");
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
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : bracket '{' should \033[0m", lin + UNU);
        printf("\033[31mbe on the same line with 'while'.\033[0m\n");
        (*error)++;
    }

    if (*p && *p != ' ') {
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : there should be a space \033[0m", lin + UNU);
        printf("\033[31mbetween 'do' and bracket '{'.\033[0m\n");
        (*error)++;
    }

    p += UNU;
    if (*p == ' ') {
        printf("\033[31m%s : ERROR : \033[0m", f_name);
        printf("\033[31mline %d : too many spaces \033[0m", lin + UNU);
        printf("\033[31mbetween 'while' and bracket '{'.\033[0m\n");
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
        printf("\033[32m%s : ERROR : \033[0m", f_name);
        printf("\033[32mline %d : verification with 0 ", lin + UNU);
        printf("\033[32mcan be eliminated. Keep only the expresion and the \033[0m");
        printf("\033[32mcompiler will check if it's a non-zero value.\033[0m\n");
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
        printf("\033[32m%s : ERROR : \033[0m", f_name);
        printf("\033[32mline %d : verification with 0 \033[0m", lin + UNU);
        printf("\033[32mcan be eliminated. Keep only the expresion, with a '!' in front\033[0m");
        printf("\033[32m, and the compiler will check if it's zero.\033[0m\n");
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
        printf("\033[32m%s : ERROR : \033[0m", f_name);
        printf("\033[32mline %d : verification with NULL \033[0m", lin + UNU);
        printf("\033[32mcan be eliminated. Keep only the expresion and the \033[0m");
        printf("\033[32mcompiler will check if it's a non-null value.\033[0m\n");
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
        printf("\033[32m%s : ERROR : \033[0m", f_name);
        printf("\033[32mline %d : verification with NULL ", lin + UNU);
        printf("\033[32mcan be eliminated. Keep only the expresion, with a '!' in front\033[0m");
        printf("\033[32m, and the compiler will check if it's null.\n\033[0m");
        (*error)++;
    }
}
