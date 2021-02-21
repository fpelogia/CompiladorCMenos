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
    printf("nula ? R: %d\n",arvoreSintatica == NULL);
    printf("Árvore Sintática:\n");
    imprimeArvore(arvoreSintatica);

    fclose(arq_cod_fonte);
    return 0;
}
