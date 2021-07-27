#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

// Tamanho da tabela Hash
#define SIZE 211

// Potência de dois utilizada na função hash
#define SHIFT 4

// Função hash
static int hash ( char * key ){ 
    int temp = 0;
    int i = 0;
    while (key[i] != '\0'){ 
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

// Lista Encadeada de inteiros (numero da linha)
// Utilizada para armazenar as linhas das ocorrências 
// dos símbolos da liguagem

typedef struct listaDeLinhas{ 
    int numlinha;
    struct listaDeLinhas * prox;
} * ListaDeLinhas;


// Lista de Blocos (unidades básicas da Tabela Hash)
typedef struct listaDeBlocos
   { char * nome;
     char * escopo;
     int eh_funcao; // 0: variável // 1: função
     int tamanho; // utilizado na geração de código assembly
     int id; // utilizado na geração de código assembly
     Tipo tipo; 
     ListaDeLinhas linhas;
     struct listaDeBlocos* prox;
   } * ListaDeBlocos;

//Tabela Hash
static ListaDeBlocos Tabela_hash[SIZE];


/* Procedimento insere_tab_sim insere o numero das linhas 
   e os locais de memoria na tabela de simbolos
*/
void insere_tab_sim( char * nome, int numlinha, int tamanho, char * escopo, Tipo tipo, int eh_funcao)
{ int h = hash(nome);
  ListaDeBlocos l =  Tabela_hash[h];
  while ((l != NULL) && ((strcmp(nome,l->nome) != 0) || strcmp(l->escopo,escopo)!=0 ))
    l = l->prox;
  if (l == NULL) /* variavel ainda nao esta na tabela */
  {
    l = (ListaDeBlocos) malloc(sizeof(struct listaDeBlocos));
    l->nome = nome;
    l->linhas = (ListaDeLinhas) malloc(sizeof(struct listaDeLinhas));
    l->linhas->numlinha = numlinha;
    l->tamanho = tamanho;
    //====================
    if(eh_funcao == 0){
        l->id = ++numlocals[indiceEscopo(escopo)]; // utilizado no gerador de cod. asm
    }
    //====================

    if(strcmp(escopo,"global")==0){
        char* eg = malloc(7*sizeof(char));
        if(eg == NULL){printf("Erro de alocação de memória!\n");return;}
        eg[0] ='g';eg[1]='l';eg[2]='o';eg[3]='b';eg[4]='a';eg[5]='l';eg[6]='\0';
        l->escopo = eg;
    }else{
        l->escopo = escopo;
    }
    l->tipo = tipo;
    l->eh_funcao = eh_funcao;
    l->linhas->prox = NULL;
    l->prox = Tabela_hash[h];
    Tabela_hash[h] = l; 
  }else/* encontrado na tabela, logo, apenas adicionar o numero da linha */
  { 
    /*if(l->tipo != tipo){
        printf("Erro semântico na linha %d:\n\tVariável %s sendo utilizada de forma incorreta!\n", numlinha, nome);
        return;
    }*/
    ListaDeLinhas t = l->linhas;
    while (t->prox != NULL) t = t->prox;
    t->prox = (ListaDeLinhas) malloc(sizeof(struct listaDeLinhas));
    t->prox->numlinha = numlinha;
    t->prox->prox = NULL;
  }
} /* insere_tab_sim */


// Função que retorna 1 se houver uma funçao de mesmo nome declarada
// e retorna 0 caso contrário.
int func_ja_declarada (char * nome){
    int h = hash(nome);
    ListaDeBlocos l =  Tabela_hash[h];
    while ((l != NULL) && ((strcmp(nome,l->nome) != 0)||(l->eh_funcao == 0))){
        l = l->prox;
    }
    if (l == NULL) {
        return 0;
    }else{
        return 1;
    }
}

// Função que retorna 1 se houver uma variável de mesmo nome declarada
// e retorna 0 caso contrário.
int var_ja_declarada (char * nome){
    int h = hash(nome);
    ListaDeBlocos l =  Tabela_hash[h];
    while ((l != NULL) && ((strcmp(nome,l->nome) != 0)||(l->eh_funcao == 1))){
        l = l->prox;
    }
    if (l == NULL) {
        return 0;
    }else{
        return 1;
    }
}

//Função que retorna 1 se já houver uma variavel decladara no escopo 
//com o mesmo nome e retorna 0 caso contrário
int var_ja_declarada_no_escopo(char *nome, char* escopo){
    int h = hash(nome);
    ListaDeBlocos l =  Tabela_hash[h];
    while (l != NULL){
        if((l->eh_funcao==0&&strcmp(nome, l->nome)==0)&&(strcmp(escopo,l->escopo)==0)){
            break;
        }
        l = l->prox;
    }
    if (l == NULL) {
        return 0;
    }else{
        return 1;
    }
}

//Função que retorna 1 se houver uma variável global com o nome dado e
// retorna 0 caso contrário
int var_tem_global(char *nome){
    int h = hash(nome);
    ListaDeBlocos l =  Tabela_hash[h];
    while (l != NULL){
        if((l->eh_funcao==0&&strcmp(nome, l->nome)==0)&&(strcmp(l->escopo,"global")==0)){
            break;
        }
        l = l->prox;
    }
    if (l == NULL) {
        return 0;
    }else{
        return 1;
    }
}

// Função que retorna o tipo de uma dada função
// assume-se que a função está declarada.
void retorna_tipo_func (char* nome, Tipo* tipo_c){
    int h = hash(nome);
    ListaDeBlocos l =  Tabela_hash[h];
    while ((l != NULL) && ((strcmp(nome,l->nome) != 0)||(l->eh_funcao == 0))){
        l = l->prox;
    }
    if (l != NULL) {
        *tipo_c = l->tipo;
    }
}

// Função que retorna o tipo de uma dada variável
// assume-se que a função está declarada.
void retorna_tipo_var (char* nome, char* escopo, Tipo* tipo_c){
    int h = hash(nome);
    ListaDeBlocos l =  Tabela_hash[h];
    while ((l != NULL) && ((strcmp(nome,l->nome) != 0)|| (strcmp(escopo,l->escopo) != 0) ||(l->eh_funcao == 1))){
        l = l->prox;
    }
    if (l != NULL) {
        *tipo_c = l->tipo;
    }
}

// Função que retorna o id de uma certa variável.
// É utilizada na geração do código assembly
int var_id(char * nome, char* escopo){
    int h = hash(nome);
    ListaDeBlocos l =  Tabela_hash[h];
    while (l != NULL){
        if ((l->eh_funcao == 0)&&(strcmp(nome,l->nome) == 0)&&(strcmp(escopo, l->escopo) == 0)){
            break;
        }
        l = l->prox;
    }
    if (l != NULL) {//encontrou a variável
        return l->id;// retorna o id da variável
    }
    return -1; // espero que nunca chegue aqui, mas sei lá...
}

/* Procedimento imprimeTabSim imprime
*   uma lista formatada do conteudo da tabela de simbolos
*   para o arquivo listing
*/

void imprimeTabSim(FILE * listing)
{ int i;
  fprintf(listing," | Nome:      Id:   Tipo:   Escopo:    Tamanho:   Referenciado nas Linhas:\n");
  fprintf(listing," | -----      ---  ------  -------     -------     ------------------------\n");
  for (i=0;i<SIZE;++i)
  { if (Tabela_hash[i] != NULL)
    { ListaDeBlocos l = Tabela_hash[i];
      while (l != NULL)
      { ListaDeLinhas t = l->linhas;
        fprintf(listing," |  %-6s ",l->nome);
        fprintf(listing," |  %-1d ",l->id);
        fprintf(listing," |  %-5s ",retStrTipo(l->tipo));
        fprintf(listing,"|  %-9s",l->escopo);
        fprintf(listing,"|  %-5d|",l->tamanho);
        while (t != NULL)
        { fprintf(listing,"%4d ",t->numlinha);
          t = t->prox;
        }
        fprintf(listing,"\n");
        l = l->prox;
      }
    }
  }
  fprintf(listing," ------------------------------------------------------------\n");
} /* printSymTab */
