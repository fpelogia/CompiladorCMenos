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
     Tipo tipo; 
     ListaDeLinhas linhas;
     int numbloco ; // utilizado ao criar
     struct listaDeBlocos* prox;
   } * ListaDeBlocos;

//Tabela Hash
static ListaDeBlocos Tabela_hash[SIZE];


/* Procedimento insere_tab_sim insere o numero das linhas 
   e os locais de memoria na tabela de simbolos
*/

void insere_tab_sim( char * nome, int numlinha, int loc, char * escopo, Tipo tipo, int eh_funcao)
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
    l->numbloco = loc;
    l->escopo = escopo;
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

/* Função consulta_tab_sim retorna a localização
 * de memoria de uma variavel ou -1 caso contrario
 */
int consulta_tab_sim ( char * nome , char * escopo)
{ int h = hash(nome);
  ListaDeBlocos l =  Tabela_hash[h];
  while ((l != NULL) && (strcmp(nome,l->nome) != 0)) //percorre a lista até ela ser vazia ou achar a var
    l = l->prox;
  if ((l == NULL)) return -1; //nao encontrado, primeira vez declarada
  else{ //encontrado
    if (strcmp(escopo, l->escopo) != 0 ){ //variavel decalarada num escopo diferente
       if(l->eh_funcao == 1){ // declaração de função
           if(strcmp(l->escopo,"global") != 0){
              return -1;
           }else{
              return l->numbloco;
           }
       }else{//declaração de variável
           return -1; //existe var com mesmo nome mas em outro escopo (talvez até global)
           //permite criar!
       }
    }
    else{
      return l->numbloco;
    }
  }
}

// Consulta presença de uma função na TS e também devolve
// o tipo dela, caso encontre.
// Retorna -1 caso não encontre no escopo atual
int consulta_tab_sim_cham ( char * nome , char * escopo, Tipo* tipo_c)
{ int h = hash(nome);
  ListaDeBlocos l =  Tabela_hash[h];
  while ((l != NULL) && (strcmp(nome,l->nome) != 0)) //percorre a lista até ela ser vazia ou achar a var
    l = l->prox;
  if ((l == NULL)) return -1; //nao encontrado, primeira vez declarada
  else{ //encontrado
    if (strcmp(escopo, l->escopo) != 0 ){ //variavel decalarada num escopo diferente
      return -1;
    }
    else{
        *tipo_c = l->tipo;//herda tipo a partir da tabela
        return l->numbloco;
    }
  }
}
        
// Usada para lidar com uso de variáveis
int consulta_tab_sim_uso_var ( char * nome , char * escopo, Tipo* tipo_c)
{ int h = hash(nome);
  ListaDeBlocos l =  Tabela_hash[h];
  while ((l != NULL) && (strcmp(nome,l->nome) != 0)) //percorre a lista até ela ser vazia ou achar a var
    l = l->prox;
  if ((l == NULL)) return -1; //nao encontrado, primeira vez declarada
  else{ //encontrado
    if (strcmp(escopo, l->escopo) != 0  ){ //variavel decalarada num escopo diferente
        if(strcmp(l->escopo, "global")!=0){
            return -1;//não era global. erro
        }else{
            return l->numbloco;
        }
    }else{
        *tipo_c = l->tipo; //herda tipo a partir da tabela
        if(strcmp(l->escopo, "global") == 0){
            return l->numbloco;
        }else{
            return -2;
        }
    }
  }
}



/* Procedimento imprimeTabSim imprime
*   uma lista formatada do conteudo da tabela de simbolos
*   para o arquivo listing
*/

void imprimeTabSim(FILE * listing)
{ int i;
  fprintf(listing," | Nome:  Nro. bloco  Tipo:   Escopo:   Referenciado nas Linhas:\n");
  fprintf(listing," | -----  ----------  ------  -------  ------------------------\n");
  for (i=0;i<SIZE;++i)
  { if (Tabela_hash[i] != NULL)
    { ListaDeBlocos l = Tabela_hash[i];
      while (l != NULL)
      { ListaDeLinhas t = l->linhas;
        fprintf(listing," |  %-6s ",l->nome);
        fprintf(listing," |  %-2d ",l->numbloco);
        fprintf(listing," |  %-5s ",retStrTipo(l->tipo));
        fprintf(listing,"|  %-11s|",l->escopo);
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
