#include "definitions.h"

//contador para os endereços na lista de blocos
static int location = 0;
static bool possuiMain = false;
static char* escopo = "global";
bool Erro;


// Insere nós na tabela de símbolos 
// Caso já presente, atualiza lista com as linhas
static void insereNo( NoArvore * t){ 
    switch (t->tipo_de_no){
        case TDecl:
            switch (t->tipo.decl){ 
                case D_func:
                    if(strcmp(t->atrib.nome,"main")==0){
                        possuiMain = true;
                    }
                    if(strcmp(t->atrib.nome,"input")==0 || strcmp(t->atrib.nome,"output")==0){
                        Erro = 1;
                        printf("Erro Semântico na linha %d\n\tFunção %s é reservada!\n",t->numlinha,t->atrib.nome);
                    }
                    if (consulta_tab_sim(t->atrib.nome) == -1){
                        insere_tab_sim(t->atrib.nome,t->numlinha,location++,"global",t->tipo_c,1);
                        escopo = t->atrib.nome;// escopo da função
                    }else{
                        Erro = 1;
                        printf("Erro Semântico na linha %d\n\tFunção %s já declarada!\n",t->numlinha,t->atrib.nome);
                    }
                    break;
                case D_var:
                    if (consulta_tab_sim(t->atrib.nome) == -1)
                        insere_tab_sim(t->atrib.nome,t->numlinha,location++,escopo,t->tipo_c,0);
                    else{
                        Erro = 1;
                        printf("Erro Semântico na linha %d\n\tVariável %s já declarada!\n",t->numlinha,t->atrib.nome);
                    }
                    break;
                default:
                     break;
            }
            break;
        case TStmt:
            switch (t->tipo.stmt){ 
                case S_Chamada:

                    if(strcmp(t->atrib.nome,"input")==0){
                        //input
                    }else if(strcmp(t->atrib.nome,"output")==0){
                        //output
                    }else if (consulta_tab_sim(t->atrib.nome) == -1){
                        Erro = 1;
                        printf("Erro Semântico na linha %d\n\tFunção %s não declarada!\n",t->numlinha,t->atrib.nome);
                    }else
                        insere_tab_sim(t->atrib.nome,t->numlinha,0,escopo,Void,1);//ultimos 4 parâmetros não são utilizados
                    break;
                default:
                     break;
            }
            break;
        case TExp:
            switch (t->tipo.exp){
                case E_Id:
                    if(strcmp(t->atrib.nome,"void")!=0){
                        if (consulta_tab_sim(t->atrib.nome) == -1){
                            Erro = 1;
                            printf("Erro Semântico  na linha %d\n\tVariável %s não declarada no escopo local!\n",t->numlinha,t->atrib.nome);
                        }else
                            insere_tab_sim(t->atrib.nome,t->numlinha,0,escopo,t->tipo_c,0);
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}


static void typeError(NoArvore * t, char * message){
    if(t->atrib.nome)
        fprintf(stdout,"Erro sintático:%s na linha %d:\n\t%s\n", t->atrib.nome, t->numlinha, message);
    else
        fprintf(stdout,"Erro sintático na linha %d:\n\t%s\n", t->numlinha, message);
  //Erro = true;
}

// Função que faz checagem de tipo em um dado nó
static void checaNo(NoArvore * t){
    switch (t->tipo_de_no){ 
        case TExp:
            switch (t->tipo.exp){
                case E_Op:
                    if ((t->filho[0]->tipo_c != Integer) ||(t->filho[1]->tipo_c != Integer))
                        typeError(t,"Operação aplicada entre não inteiros!");
                    if ((t->atrib.op == IGUALIGUAL) || (t->atrib.op == DIF)|| (t->atrib.op == MENOR)|| (t->atrib.op == MENIGUAL)|| (t->atrib.op == MAIOR)|| (t->atrib.op == MAIIGUAL))
                        t->tipo_c = Boolean;
                    else
                        t->tipo_c = Integer;
                    break;
                case E_Num:
                case E_Id:
                    t->tipo_c = Integer;
                    break;
                default:
                    break;
            }
            break;
        case TStmt:
            switch (t->tipo.stmt){
                case S_If:
                    if (t->filho[0]->tipo_c == Integer)
                        typeError(t->filho[0],"Condicional do If não Booleano");
                    break;
                case S_Atrib:
                    if (t->filho[0]->tipo_c != Integer)
                        typeError(t->filho[0],"Atribuição de valor não inteiro");
                    break;
               // case WriteK:
               //     if (t->filho[0]->tipo_c != Integer)
               //         typeError(t->filho[0],"write of non-integer value");
               //     break;
                case S_While:
                    if (t->filho[1]->tipo_c == Integer)
                        typeError(t->filho[1],"Condicional do While não Booleano");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
      }
}
// Faz percurso "pré-ordem" em uma árvore inserindo seus
// nós na tabela de símbolos
static void percorre(NoArvore * arv){ 
    if (arv != NULL){ 
        insereNo(arv);//processa nó pai antes dos filhos
        int i;
        for (i=0; i < MAXFILHOS; i++){
            percorre(arv->filho[i]);//processa filhos da esquerda para a direita
        }
        checaNo(arv);
        percorre(arv->irmao);
      }
}

// Função que faz a checagem de tipos a partir da árvore sintática
void checaTipos(NoArvore * arv){
    percorre(arv);
}

//Função que monta a tabela de símbolos a partir da árvore sintática
void montaTabSim(NoArvore * arv){ 
    percorre(arv);
    if(!possuiMain){
        fprintf(stdout,"\nErro Semântico: Função principal (main) não declarada\n");
    }else{
        fprintf(stdout,"\nTabela de Símbolos:\n\n");
        imprimeTabSim(stdout);
    }
}
