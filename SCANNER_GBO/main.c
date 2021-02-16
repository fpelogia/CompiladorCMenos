#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#define MAX_LINHA 100
int main(){
    FILE* f = fopen("sample.c","r");
    FILE* fc = fopen("sample.c","r");
    if(f == NULL){
        perror("Falha na leitura do arquivo");
    }
    char linha[MAX_LINHA];
    //while(fgets(linha, MAX_LINHA, f) != NULL){
    while(1){
        if(fgets(linha, MAX_LINHA, fc) == NULL){
            break;
        }
        printf("\n%d: %s",yylineno, linha);
        Token rt;
        do{
            rt = retornaToken(f);
            if(rt == ENTER) break;
            if(rt == ID || rt == NUM){
                printf("\t%d: %s, val= %s\n",yylineno, nome_token[rt], yytext);
            }else{
                printf("\t%d: %s\n",yylineno, nome_token[rt]);
            }
        }while(1);
        //if(retornaToken(f) == 0){
        //    break;
        //}
    }
    fclose(f);
    fclose(fc);
    return 0;
}
