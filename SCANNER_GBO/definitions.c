#include "definitions.h"


char* nome_token[] ={"FIMARQ", "ERRO",
    "ELSE", "IF", "INT", "RETURN", "VOID", "WHILE",
    "ID","NUM",
    "IGUAL", "IGUALIGUAL", "DIF", "MENOR", "MAIOR", "MENIGUAL", "MAIIGUAL", "MAIS", "MENOS",
    "VEZES", "DIV", "ABREPAR", "FECHAPAR", "PVIRG", "VIRG", "ABRECOL", "FECHACOL", "ABRECH", "FECHACH", "COMENT", "ENTER"
};

/*char* nome_token(Token t){
    char *nome;
    nome = malloc(MAX_TOKEN_NAME*sizeof(char));
    switch(t){
        case FIMARQ:
            strcpy(nome,"fim do arquivo (EOF)");
            break;
        case ERRO:
            strcpy(nome,"Erro !");
            break;
        case ELSE:
            strcpy(nome,"ELSE");
            break;
        case IF:
            strcpy(nome,"IF");
            break;
        case INT:
            strcpy(nome,"INT");
            break;
        case RETURN:
            strcpy(nome,"RETURN");
            break;
        case VOID:
            strcpy(nome,"VOID");
            break;
        case WHILE:
            strcpy(nome,"WHILE");
            break;
        case ID:
            strcpy(nome,"ID");
            break;
        case NUM:
            strcpy(nome,"NUM");
            break;
        case IGUAL:
            strcpy(nome,"IGUAL");
            break;
        case IGUALIGUAL:
            strcpy(nome,"IGUALIGUAL");
            break;
        case DIF:
            strcpy(nome,"DIF");
            break;
        case MENOR:
            strcpy(nome,"MENOR");
            break;
        case MAIOR:
            strcpy(nome,"MAIOR");
            break;
        case MENIGUAL:
            strcpy(nome,"MENIGUAL");
            break;
        case MAIIGUAL:
            strcpy(nome,"MAIIGUAL");
            break;
        case MAIS:
            strcpy(nome,"MAIS");
            break;
        case MENOS:
            strcpy(nome,"MENOS");
            break;
        case VEZES:
            strcpy(nome,"VEZES");
            break;
        case DIV:
            strcpy(nome,"DIV");
            break;
        case ABREPAR:
            strcpy(nome,"ABREPAR");
            break;
        case PVIRG:
            strcpy(nome,"PVIRG");
            break;
        case VIRG:
            strcpy(nome,"VIRG");
            break;
        case ABRECOL:
            strcpy(nome,"ABRECOL");
            break;
        case FECHACOL:
            strcpy(nome,"FECHACOL");
            break;
        case ABRECH:
            strcpy(nome,"ABRECH");
            break;
        case FECHACH:
            strcpy(nome,"FECHACH");
            break;
        case COMENT:
            strcpy(nome,"COMENT");
            break;
        case ESPACO:
            strcpy(nome,"ESPACO");
            break;
        case ENTER:
            strcpy(nome,"ENTER");
            break;
        default:
            strcpy(nome, "OUTRO-FALTA-ESCREVER");
            break;
    }
    return nome;
}
*/
