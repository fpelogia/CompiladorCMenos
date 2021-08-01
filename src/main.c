#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#define MAX_LINHA 100
//aloca as variaveis globais
int numlinha = 0;
FILE * arq_cod_fonte;
bool Erro;

char* lista_escopos[MAX_FUNC_DECL];
int tam_lista_escopos = 0;
int numlocals[MAX_FUNC_DECL];//número de variáveis de certo escopo

int main(int argc, char** argv){

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
    
    // utilizado na geração de código Intermediário
    registraEscopo("global");

    montaTabSim(arvoreSintatica);
    if(!Erro)
        checaTipos(arvoreSintatica);

    
    printf("\n\n============  Código Intermediário ============\n\n");
    inicializaListaQuad(&CodInter);
    //inicializa_reg_escopo();
    if(!Erro)
        geraCod(arvoreSintatica);
    
    imprimeListaQuad(&CodInter); // Imprime Código Intermediário

    printf("\n=============== Código Assembly ==================\n\n");
    inicializaListaInstrAsm(&CodAsm);
    percorreListaQuad(&CodInter); // Imprime Código Assembly

    preencheEnderecosASM(&CodAsm);

    // [TODO] Escrever funções para destruir Árvore, LQ, LIA
    //  darv
    //destroiListaQuad(&CodInter); 
    //destroiListaInstrAsm(&CodAsm); //nao funciona ainda

    fclose(arq_cod_fonte);
    return 0;
}



