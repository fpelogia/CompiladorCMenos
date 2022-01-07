#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* converte_n_bin(int x, int n){
    // 30 é maior do que qualquer campo
    char str[30] = {'\0'};
    char* inv = calloc(30, sizeof(char));
    int tam = 0;
    int negativo = (x < 0);

    x = (x >= 0)?x:-x; // x = |x|

    while(x >= 2){
        if(x%2 == 0)
            str[tam++] = '0';
        else
            str[tam++] = '1';
        x /= 2;
    }
    
    if(x == 0){
        str[tam] = '0';
    }else{
        str[tam] = '1';
    }

    int i, extra = n - tam - 1;
    for(i = 0; i < extra; i ++){
        inv[i] = '0';
    }
    for(i = 0; i <= tam; i ++){
        inv[extra + i] = str[tam - i];
    }

    // lógica do compl. de 2 : se negativo, inverter bits e somar 1
    if(negativo){
        for(i = 0; i < strlen(inv); i ++){
            if(inv[i] == '0'){
                inv[i] = '1';
            }else{
                inv[i] = '0';
            }
        }
        tam = strlen(inv);
        if(inv[tam] == '0')
            inv[tam] = '1';
        else{
            int temp = tam-1;
            while(inv[temp] != '0'){
                inv[temp] = '0';
                temp--;
            }
            inv[temp] = '1';
        }
    }
    return inv;
}

int main(int argc, char** argv){
    int x = 9;
    char* bin;

    do{
        printf("\nDigite um número inteiro\n");
        scanf("%d", &x);
        bin = converte_n_bin(x, 12);
        printf("Bin(%d) = %s\n", x, bin);
        free(bin);
    }while(1);

    return 0;
}
