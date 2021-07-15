#include <definitions.h>
#include <stdint.h>
#define MEM_SLOTS 64 // 64 slots de 32 bits cada 

typedef uint32_t endereco_m;

typedef struct area_ativacao_s {
    endereco_m func_fp; // endereço de memória da área de ativação 
    endereco_m quem_chamou; // endereço de memória da função que chamou
    int32_t valor_retorno; // valor de retorno da função
    variavel *lista_args; // lista de argumentos
    variavel *lista_var_locais; // lista de variáveis locais
    struct area_ativacao_s *prox;// próxima área de ativação
} area_ativacao;


typedef struct variavel_s {
    int deslocamento;// deslocamento em relação ao endereço
    char *nome; // nome da variável
    int32_t conteudo; //conteudo da variável
    struct variavel_s* prox;
}variavel;

/*
 * Pensar nas funções de interface
 * */


