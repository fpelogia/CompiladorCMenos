#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#define MAX_LINHA 100
//aloca as variaveis globais
int numlinha = 0;
FILE * arq_cod_fonte;

int main(){
    arq_cod_fonte = fopen("sample.c","r");
    if(arq_cod_fonte == NULL){
        perror("Falha na leitura do arquivo");
    }

    NoArvore* arvoreSintatica;
    arvoreSintatica = parse();
   /* NoArvore* no;
    no = arvoreSintatica;
    printf("1)tipo_de_no: %d\n",no->tipo_de_no);
    printf("1)tipo de retorno: %d\n",no->tipo_c);
    printf("1)nomefunc: %s\n",no->atrib.nome);*/
    printf("\n\nÁrvore Sintática:\n");
    imprimeArvore(arvoreSintatica);
    montaTabSim(arvoreSintatica);

    fclose(arq_cod_fonte);
    return 0;
}
