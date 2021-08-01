#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#define MAX_LINHA 100
//aloca as variaveis globais
int numlinha = 0;
FILE * arq_cod_fonte;
FILE * arq_cod_bin;
bool Erro;

char* lista_escopos[MAX_FUNC_DECL];
int tam_lista_escopos = 0;
int numlocals[MAX_FUNC_DECL];//número de variáveis de certo escopo

int main(int argc, char** argv){
    // Lê nome do arquivo e opções, se houver
    if(argc < 2){
        arq_cod_fonte = fopen("sample.c","r");
    }else{
        arq_cod_fonte = fopen(argv[1],"r");
    }
    if(arq_cod_fonte == NULL){
        printf("Falha na leitura do código fonte\n");
        return 1;
    }

    printf("\n====================== Análise Léxica ===========================\n");
    if(argc < 2){
        imprimeTokens("sample.c");    
    }else{
        imprimeTokens(argv[1]);    
    }
    fclose(arq_cod_fonte);
    if(argc < 2){
        arq_cod_fonte = fopen("sample.c","r");
    }else{
        arq_cod_fonte = fopen(argv[1],"r");
    }
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

    if(argc < 2){
        arq_cod_bin = fopen("sample","w");
    }else{
        char* nome_saida;
        if(argc > 3){
            if(strcmp(argv[2], "-o")==0){
                nome_saida = strdup(argv[3]);
            }else{
                nome_saida = strndup(argv[1], strlen(argv[1]) - 2);
            }
        }else{
            nome_saida = strndup(argv[1], strlen(argv[1]) - 2);
        }
        arq_cod_bin = fopen(nome_saida,"w");
        free(nome_saida);
    }
    if(arq_cod_bin == NULL){
        printf("Falha ao gerar arquivo de saída! \n");
        return 1;
    }

    printf("\n=============== Código Binário ==================\n\n");
    preencheEnderecosASM(&CodAsm);
    imprimeCodBin();
    // [TODO] Escrever funções para destruir Árvore, LQ, LIA
    //  darv
    //destroiListaQuad(&CodInter); 
    //destroiListaInstrAsm(&CodAsm); //nao funciona ainda

    fclose(arq_cod_fonte);
    fclose(arq_cod_bin);
    return 0;
}



