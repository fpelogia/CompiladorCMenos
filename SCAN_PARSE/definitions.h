#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TOKEN_NAME 100
typedef enum{
    FIMARQ, ERRO,
    ELSE, IF, INT, RETURN, VOID, WHILE,
    ID,NUM,
    IGUAL, IGUALIGUAL, DIF, MENOR, MAIOR, MENIGUAL, MAIIGUAL, MAIS, MENOS,
    VEZES, DIV, ABREPAR, FECHAPAR, PVIRG, VIRG, ABRECOL, FECHACOL, ABRECH, FECHACH, COMENT, ENTER
} Token;

extern char* nome_token[];

extern int yylineno;
extern char* yytext;

// Função definida com ajuda da ferramenta flex
Token retornaToken(FILE* arq);

