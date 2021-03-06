#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h> // int32_t e uint32_t

#define MAX_TAM_TOKEN 100

#define MEM_SLOTS 64 // 64 slots de 32 bits cada 

#define MAX_FUNC_DECL 50 // máximo de funções a serem declaradas

#define GLOBAL_PART_SIZE 30 // numero de slots da memória para as coisas globais

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
extern bool Erro;
extern char* yytext;
extern int numlinha;
extern FILE* arq_cod_fonte; // arquivo com o código fonte a ser compilado
extern char lexema[MAX_TAM_TOKEN + 1]; // armazena string do token reconhecido pelo scanner
extern char ID_nome[MAX_TAM_TOKEN + 1]; // armazena lexema (nome) de tokens ID
extern char NUM_val[MAX_TAM_TOKEN + 1]; // armazena string com valor de tokens NUM


#define MAX_LINHA 100
// Roda scanner e imprime os tokens reconhecidos e seus lexemas
void imprimeTokens(char* nomearq);



typedef int Token; // yacc define automaticamente os valores inteiros dos Tokens

//==========  (Definição das estruturas de Árvore Sintática)  ==============

typedef enum {TDecl,TExp,TStmt} TipoNo;
typedef enum {D_var, D_func, D_Tipo} TipoDecl;
typedef enum {S_If,S_While,S_Atrib,S_Retorno,S_Chamada} TipoStmt;
typedef enum {E_Op,E_Num,E_Id} TipoExp;
typedef enum {Void,Integer,Array,Boolean} Tipo; // Usado para verificação de tipo

#define MAXFILHOS 3

typedef struct noArvore{
    struct noArvore * filho[MAXFILHOS];
    struct noArvore * irmao;
    int numlinha;
    TipoNo tipo_de_no;
    union { TipoDecl decl; TipoStmt stmt; TipoExp exp;} tipo; //talvez melhorar o nome
    union { Token op;
            int val;
            char * nome; } atrib;
    Tipo tipo_c; // para checar tipos em expressões
} NoArvore;

char * copiaString(char * s);
// Função que retorna o nome do token (para impressão na tela)
char* nome_token(Token token);
// Função definida com ajuda da ferramenta flex (lex)
Token retornaToken();
// Função definida com ajuda da ferramenta bison (yacc)
NoArvore* parse(void);

void imprimeArvore( NoArvore * arv );

NoArvore * novoNoDecl(TipoDecl tipo);

NoArvore * novoNoStmt(TipoStmt tipo);

NoArvore * novoNoExp(TipoExp tipo);

char * retStrTipo(Tipo t);


/* Procedimento insere_tab_sim insere o numero das linhas 
   e os locais de memoria na tabela de simbolos
*/
void insere_tab_sim( char * nome, int numlinha, int loc, char * escopo, Tipo tipo, int eh_funcao);

// Função que retorna 1 se houver uma funçao de mesmo nome declarada
// e retorna 0 caso contrário.
int func_ja_declarada (char * nome);

// Função que retorna 1 se houver uma variável de mesmo nome declarada
// e retorna 0 caso contrário.
int var_ja_declarada (char * nome);

//Função que retorna 1 se já houver uma variavel decladara no escopo 
//com o mesmo nome e retorna 0 caso contrário
int var_ja_declarada_no_escopo(char *nome, char* escopo);

// Função que retorna o tipo de uma dada função
// assume-se que a função está declarada.
void retorna_tipo_func (char *nome, Tipo* tipo_c);

// Função que retorna o tipo de uma dada variável
// assume-se que a função está declarada.
void retorna_tipo_var (char* nome, char* escopo, Tipo* tipo_c);

//Função que retorna 1 se houver uma variável global com o nome dado e
// retorna 0 caso contrário
int var_tem_global(char *nome);

/* Procedimento imprimeTabSim imprime
*   uma lista formatada do conteudo da tabela de simbolos
*   para o arquivo listing
*/
void imprimeTabSim(FILE * listing);

//Função que monta a tabela de símbolos a partir da árvore sintática
void montaTabSim(NoArvore * arv); 

// Função que faz a checagem de tipos a partir da árvore sintática
void checaTipos(NoArvore * arv);

// Função que gera o código intermediário de 3 endereços
// a partir da árvore sintática e o armazena no arquivo
// arq

//==================================== Pilha ====================================
void geraCod(NoArvore * arv);

typedef struct SNome{
    char *nome;
    struct SNome *abaixo;
}TNome;

typedef struct {
    int numelementos;
    TNome* topo;
}Pilha;

void push(Pilha *P, char* nome);
char* pop(Pilha *P);
void inicializaPilha(Pilha *P);

//==================== Geração de Cód. Intermediário =========================
typedef struct {
    char* op;
    char* c1;
    char* c2;
    char* c3;
}Quad;

typedef struct SNoQuad{
    Quad *quad;
    struct SNoQuad *prox;
}NoQuad;

typedef struct{
    NoQuad* prim;
}ListaQuad;

void inicializaListaQuad(ListaQuad *lq);
void insereQuad(ListaQuad* lq, char* op, char* c1, char* c2, char*c3);
void imprimeListaQuad(ListaQuad *lq);

extern ListaQuad CodInter; // variável global com a lista de quádruplas (cod. intermediário)

// =================== Geração de Código Assembly =============================

extern char* lista_escopos[MAX_FUNC_DECL];
extern int tam_lista_escopos;
extern int numlocals[MAX_FUNC_DECL];//número de variáveis de certo escopo

void registraEscopo(char* escopo);
int indiceEscopo(char* escopo);

void percorreListaQuad(ListaQuad *lq);
void gera_asm_R(char* op, char* c1, char* c2, char* c3);
int eh_operacao(char* op);
int var_id(char * nome, char* escopo); // corpo está em symtab.c
void gera_asm_LOAD(char* c1, char* c2);
void gera_asm_FUN(char* nome);
void gera_asm_ASSIGN(char* c1, char* c2);
void gera_asm_STORE(char* c1, char* c2);
void gera_asm_RET(char* c1);
void gera_asm_LAB(char* c1);
void gera_asm_END(char* c1);

// jeito que acho que deve ser:
//typedef uint32_t endereco_m;
typedef char* endereco_m; // por enquanto, para testar, seja o nome da funcao

/*
typedef struct variavel_s {
    int deslocamento;// deslocamento em relação ao endereço
    char *nome; // nome da variável
    int32_t conteudo; //conteudo da variável
    struct variavel_s* prox;
}variavel;
*/
/*
typedef char* variavel; // por enquanto, para testar, seja o nome da variavel

typedef struct area_ativacao_s {
    endereco_m func_fp; // endereço de memória da área de ativação 
    endereco_m quem_chamou; // endereço de memória da função que chamou
    int32_t valor_retorno; // valor de retorno da função
    variavel *lista_args; // lista de argumentos
    variavel *lista_var_locais; // lista de variáveis locais
    struct area_ativacao_s *prox;// próxima área de ativação
} area_ativacao;

// Guarda dados referentes às funções chamadas
area_ativacao *listaChamadas;// Lista com as áreas de ativação


void cadastraChamada(endereco_m func, endereco_m escopo, variavel* lista_args){
    area_ativacao* lc_p = listaChamadas;
    while(lc_p->prox != NULL){
        lc_p = lc_p->prox;
    }
    area_ativacao* nova_aa = malloc(sizeof(area_ativacao));
    nova_aa->func_fp = func;
    nova_aa->quem_chamou = escopo;

}

*/
/*
 * Pensar nas funções de interface
 * */



