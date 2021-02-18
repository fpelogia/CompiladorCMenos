#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_TOKEN 100

#ifndef YYPARSER // Não importa o arquivo quando chamado pelo parse.y
#include "parse.tab.h" //Gerado pela flag "-d" do bison
#define ENDFILE 0
#endif

/*
typedef enum{
    FIMARQ, ERRO,
    ELSE, IF, INT, RETURN, VOID, WHILE,
    ID,NUM,
    IGUAL, IGUALIGUAL, DIF, MENOR, MAIOR, MENIGUAL, MAIIGUAL, MAIS, MENOS,
    VEZES, DIV, ABREPAR, FECHAPAR, PVIRG, VIRG, ABRECOL, FECHACOL, ABRECH, FECHACH, COMENT, ENTER
} Token;
*/

extern int yylineno;
extern char* yytext;
extern bool erro;
extern int numlinha;
extern FILE* arq_cod_fonte; // arquivo com o código fonte a ser compilado
extern char tokenString[MAX_TAM_TOKEN + 1]; // armazena string do token reconhecido pelo scanner

// Função que retorna o nome do token (para impressão na tela)
char* nome_token(Token token);
// Função definida com ajuda da ferramenta flex (lex)
Token retornaToken();
// Função definida com ajuda da ferramenta bison (yacc)
NoArvore* parse(void);

typedef int TokenType; // yacc define automaticamente os valores inteiros dos Tokens

//==========  (Definição das estruturas de Árvore Sintática)  ==============

typedef enum {TDecl,TExp,TStmt} TipoNo;
typedef enum {D_var, D_func} TipoDecl;
typedef enum {S_If,S_While,S_Else,S_Return,S_Params} TipoStmt;
typedef enum {T_Operador,T_Num,T_Id} TipoExp;
typedef enum {Void,Integer} Tipo; // Usado para verificação de tipo

#define MAXFILHOS 3

typedef struct noArvore{
    struct noArvore * filho[MAXFILHOS];
        struct noArvore * irmao;
    int numlinha;
    TipoNo tipo_de_no;
    union { TipoDecl decl; TipoStmt stmt; TipoExp exp;} tipo; //talvez melhorar o nome
    union { TokenType op;
            int val;
            char * nome; } atrib;
    Tipo tipo; // para checar tipos em expressões
} NoArvore;



