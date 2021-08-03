#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h> // int32_t e uint32_t

// Fase de Análise
#define MAX_TAM_TOKEN 100


// Fase de Síntese
#define MEM_SLOTS 256 // 256 slots de 32 bits cada 
#define MAX_FUNC_DECL 50 // máximo de funções a serem declaradas
#define MAX_ENDERECOS 100 // tamanho máximo da lista de endereços absolutos
#define MAX_VARS_TOTAL 1000 // máximo de variáveis a serem declaradas em todo o código
#define N_GPRS 26 // número de registradores de propósito geral

#ifndef YYPARSER // Não importa o arquivo quando chamado pelo parse.y
#include "parse.tab.h" //Gerado pela flag "-d" do bison
#define ENDFILE 0
#endif

// Manipulação de Arquivos 
extern FILE* arq_cod_fonte; // arquivo com o código fonte a ser compilado
extern FILE* arq_cod_bin; // arquivo que vai receber o código binário

// Auxiliares para Análise Léxica
extern int yylineno;
extern bool Erro;
extern char* yytext;
extern int numlinha;
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
void insere_tab_sim( char * nome, int numlinha, int tamanho, char * escopo, Tipo tipo, int eh_funcao);

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
void destroiListaQuad(ListaQuad *lq);

extern ListaQuad CodInter; // variável global com a lista de quádruplas (cod. intermediário)

//=================== Gerenciamento de Registradores =====================
extern int gpr[N_GPRS]; // vetor com disponibilidade dos Registradores
// obs: vetores globais já têm seus elementos inicializados com zero
int usa_registrador();
void libera_registrador(int num);
void libera_todos_os_registradores();

// =================== Geração de Código Assembly =============================
//
// Tipos de Instrução da arquitetura RVSP (https://github.com/fpelogia/RVSP)
typedef enum{ 
    R, I, B, S, J 
}TipoAsm;

// Registradores de propósito específico
enum sprs{$zero = 0, $aux = 27, $rv = 28, $fp = 29, $sp = 30, $ra = 31};
// gprs vão de 1 a 26

typedef struct {
    int tipo;
    int rd;
    int rs1;
    int rs2;
    char* nome;
    char* imediato;//antes da segunda passada
    // imediato segura o nome da função ou label
}InstrAsm;

typedef struct SNoInstrAsm{
    InstrAsm *instr;
    struct SNoInstrAsm *prox;
}NoInstrAsm;

typedef struct{
    NoInstrAsm* prim;
}ListaInstrAsm;

void inicializaListaInstrAsm(ListaInstrAsm *lia);
void insereInstrAsm(ListaInstrAsm* lia, TipoAsm tipo, char* nome, int rd, int rs1, int rs2, char* imediato);
void destroiListaInstrAsm(ListaInstrAsm *lia);

extern ListaInstrAsm CodAsm; // variável global com a lista de instrucoes assembly


// Variáveis globais auxiliares
extern char* lista_escopos[MAX_FUNC_DECL];
extern int tam_lista_escopos;
extern int numlocals[MAX_FUNC_DECL];//número de variáveis de certo escopo

// Funções auxiliares
void registraEscopo(char* escopo); // é utilizada em analyze.c
int indiceEscopo(char* escopo);
int var_id(char * nome, char* escopo, int* eh_global); // corpo está em symtab.c
int treg_inverso ( char* tr ); // ($ti) => (i)
int eh_operacao(char* op);
int eh_comparacao(char* op);

// Funções Importantes para Geração do Código Assembly
void percorreListaQuad(ListaQuad *lq);

void gera_asm_operacao(char* op, char* c1, char* c2, char* c3);
void gera_asm_comparacao(char* op, char* c1, char* c2, char* c3);
void gera_asm_LOAD(char* c1, char* c2, char* c3);
void gera_asm_FUN(char* nome);
void gera_asm_ARG(char* c1, char* c2, char* c3);
void gera_asm_ASSIGN(char* c1, char* c2);
void gera_asm_STORE(char* c1, char* c2, char* c3);
void gera_asm_PARAM(char* c1);
void gera_asm_RET(char* c1);
void gera_asm_LAB(char* c1);
void gera_asm_IFF(char* c1, char* c2);
void gera_asm_GOTO(char* c1);
void gera_asm_END(char* c1);
void gera_asm_CALL(char* c1, char* c2, char* c3);
void gera_asm_ALLOC(char* c1, char* c2, char* c3);

// Tratamento de Endereços (para labels e funções)
typedef struct{
    char* nome;
    int endereco;
}end_abs;

extern end_abs listaEnderecos[MAX_ENDERECOS];
void preencheEnderecosASM_geraBIN(ListaInstrAsm *lia);

// ============= Geração de Código Binário ============

// Gera representação binária com número de bits especifico
char* converte_n_bin(int x, int n);

enum campos{
    c_op, c_f7, c_f3 
};

// de acordo com campo, a função pode retornar
// opcode, funct3 ou funct7 da instrucao
int opcode_f3_f7(char* nome, int campo);

void gera_bin_R(InstrAsm* instr);
void gera_bin_I(InstrAsm* instr);
void gera_bin_J(InstrAsm* instr);
void gera_bin_B(InstrAsm* instr);
// tipo S gera binário igual ao tipo B

extern char** CodBin;//código binário
void inicializaListaCodBin(int tam);//deve receber nro de instr. asm
void imprimeCodBin();

