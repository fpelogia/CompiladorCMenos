#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#define MAX_LINHA 100
//aloca as variaveis globais
int numlinha = 0;
FILE * arq_cod_fonte;
bool Erro;
int main(){

    arq_cod_fonte = fopen("sample.c","r");
    if(arq_cod_fonte == NULL){
        printf("Falha na leitura do código fonte\n");
    }

    printf("\n====================== Análise Léxica ===========================\n");
    imprimeTokens("sample.c");    
    fclose(arq_cod_fonte);
    arq_cod_fonte = fopen("sample.c","r");
    numlinha = 0;

    
    NoArvore* arvoreSintatica;
    arvoreSintatica = parse();
    printf("\n\n==================== Árvore Sintática ====================\n\n");
    if(!Erro)
        imprimeArvore(arvoreSintatica);
    printf("\n\n");

    montaTabSim(arvoreSintatica);
    if(!Erro)
        checaTipos(arvoreSintatica);

    printf("\n\n============  Código Intermediário ============\n\n");
    if(!Erro)
        geraCod(arvoreSintatica);
    
    imprimeListaQuad(&CodInter); // Imprime Código Intermediário

    percorreListaQuad(&CodInter); // Imprime Código Assembly

    printf("\n");
    fclose(arq_cod_fonte);
    return 0;
}



