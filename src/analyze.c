#include "definitions.h"

//contador para os endereços na lista de blocos
static bool possuiMain = false;
static char* escopo = "global";


static void typeError(NoArvore * t, char * message){
    if(t->tipo_de_no == TExp && t->tipo.exp == E_Id){
        fprintf(stdout,"Erro Semântico:%s na linha %d:\n\t%s\n", t->atrib.nome, t->numlinha, message);
        Erro = true;
    }else{
        fprintf(stdout,"Erro Semântico na linha %d:\n\t%s\n", t->numlinha, message);
        Erro = true;
    }
  //Erro = true;
}

// Insere nós na tabela de símbolos 
// Caso já presente, atualiza lista com as linhas
static void insereNo( NoArvore * t){ 
    Tipo *tipo_c;
    tipo_c = (Tipo*) malloc(sizeof(Tipo));
    switch (t->tipo_de_no){
        case TDecl:
            switch (t->tipo.decl){ 
                case D_func:
                    if(strcmp(t->atrib.nome,"main")==0){
                        possuiMain = true;
                    }
                    if(strcmp(t->atrib.nome,"input")==0 || strcmp(t->atrib.nome,"output")==0 || strcmp(t->atrib.nome,"hd_read")==0 || strcmp(t->atrib.nome,"hd_write")==0){
                        Erro = true;
                        printf("Erro Semântico na linha %d\n\tFunção %s é reservada!\n",t->numlinha,t->atrib.nome);
                    }else{
                        if (func_ja_declarada(t->atrib.nome)==0){
                            insere_tab_sim(t->atrib.nome,t->numlinha,0,"global",t->tipo_c,1);
                            escopo = t->atrib.nome;// escopo da função
                            registraEscopo(escopo);
                        }else{
                            Erro = true;
                            printf("Erro Semântico na linha %d\n\tFunção %s já declarada!\n",t->numlinha,t->atrib.nome);
                        }
                    }
                    break;

                case D_var: // verificar escopo
                    if(t->tipo_c == Void){
                        typeError(t,"Declaração de variável não inteira\n");
                        Erro = true;
                    }
                    if (var_ja_declarada(t->atrib.nome) == 0)
                        //variável ainda não declarada
                        //pode declarar
                        if(t->filho[0] != NULL){//vetor
                            int tamanho = t->filho[0]->atrib.val;
                            insere_tab_sim(t->atrib.nome,t->numlinha,tamanho,escopo,t->tipo_c,0);
                        }else{
                            insere_tab_sim(t->atrib.nome,t->numlinha,1,escopo,t->tipo_c,0);
                        }
                    else{
                        //variável já declarada
                        if(strcmp(escopo,"global")!=0){
                            if(var_ja_declarada_no_escopo(t->atrib.nome, escopo) == 0){
                                //pode declarar
                                if(t->filho[0] != NULL){//vetor
                                    int tamanho = t->filho[0]->atrib.val;
                                    insere_tab_sim(t->atrib.nome,t->numlinha,tamanho,escopo,t->tipo_c,0);
                                }else{
                                    insere_tab_sim(t->atrib.nome,t->numlinha,1,escopo,t->tipo_c,0);
                                }
                            }else{
                                Erro = true;
                                printf("Erro Semântico na linha %d\n\tVariável %s já declarada!\n",t->numlinha,t->atrib.nome);
                            }
                        }else{
                            Erro = true;
                            printf("Erro Semântico na linha %d\n\tVariável global %s já declarada!\n",t->numlinha,t->atrib.nome);
                        }
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
                        t->tipo_c = Integer;
                    }else if(strcmp(t->atrib.nome,"output")==0){
                        //output
                        t->tipo_c = Integer;
                    }else if(strcmp(t->atrib.nome,"hd_read")==0){
                        //hd_read
                        t->tipo_c = Integer;
                    }else if(strcmp(t->atrib.nome,"hd_write")==0){
                        //hd_write
                        t->tipo_c = Integer;
                    }else if (func_ja_declarada(t->atrib.nome) == 0){
                        Erro = 1;
                        printf("Erro Semântico na linha %d\n\tFunção %s não declarada!\n",t->numlinha,t->atrib.nome);
                    }else{
                        //atualiza linhas
                        retorna_tipo_func(t->atrib.nome,tipo_c);
                        t->tipo_c = *tipo_c;
                        insere_tab_sim(t->atrib.nome,t->numlinha,0,"global",t->tipo_c,1);
                    }
                    break;
                default:
                     break;
            }
            break;
        case TExp:
            switch (t->tipo.exp){
                case E_Id: // verificar escopo
                    if(strcmp(t->atrib.nome,"void")!=0){
                        if (var_ja_declarada(t->atrib.nome) == 0){
                            Erro = true;
                            printf("Erro Semântico  na linha %d\n\tVariável %s não declarada\n",t->numlinha,t->atrib.nome);
                        }else if (var_ja_declarada_no_escopo(t->atrib.nome, escopo) == 1){
                            //mesmo escopo
                            retorna_tipo_var(t->atrib.nome,escopo,tipo_c);
                            if(t->tipo_c == Void){
                                t->tipo_c = *tipo_c;
                            }
                            insere_tab_sim(t->atrib.nome,t->numlinha,0,escopo,t->tipo_c,0);
                        }else{//não está declarada no escopo
                            if(var_tem_global(t->atrib.nome)==0){
                                Erro = true;
                                printf("Erro Semântico  na linha %d\n\tVariável %s não declarada\n",t->numlinha,t->atrib.nome);
                            }else{
                                retorna_tipo_var(t->atrib.nome,"global",tipo_c);
                                if(t->tipo_c == Void){
                                    t->tipo_c = *tipo_c;
                                }
                                //variável é global. atualizar linhas
                                insere_tab_sim(t->atrib.nome,t->numlinha,0,"global",t->tipo_c,0);
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    free(tipo_c);
}



// Função que faz checagem de tipo em um dado nó
static void checaNo(NoArvore * t){
    switch (t->tipo_de_no){ 
        case TExp:
            switch (t->tipo.exp){
                case E_Op:
                    if ((t->filho[0]->tipo_c != Integer) ||(t->filho[1]->tipo_c != Integer))
                        typeError(t,"Operação aplicada entre não inteiros!\n");
                    else{
                        t->tipo_c = Integer;
                    }
                        
                    t->tipo_c = Integer;
                    if ((t->atrib.op == IGUALIGUAL) || (t->atrib.op == DIF)|| (t->atrib.op == MENOR)|| (t->atrib.op == MENIGUAL)|| (t->atrib.op == MAIOR)|| (t->atrib.op == MAIIGUAL))
                        t->tipo_c = Boolean;
                    else
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
                        typeError(t->filho[0],"Condicional do If não Booleano\n");
                    break;
                case S_Atrib:
                    if (t->filho[1]->tipo_c != t->filho[0]->tipo_c){
                        typeError(t->filho[1],"Atribuição com tipos diferentes\n");
                    }
                    break;
                case S_While:
                    if (t->filho[0]->tipo_c == Integer)
                        typeError(t->filho[0],"Condicional do While não Booleano\n");
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
static void percorre_pre_ordem(NoArvore * arv){ 
    if (arv != NULL){ 
        insereNo(arv);//processa nó pai antes dos filhos
        int i;
        for (i=0; i < MAXFILHOS; i++){
            percorre_pre_ordem(arv->filho[i]);//processa filhos da esquerda para a direita
        }
        percorre_pre_ordem(arv->irmao);
      }
}

// Faz percurso "pós-ordem" em uma árvore inserindo seus
// nós na tabela de símbolos
static void percorre_pos_ordem(NoArvore * arv){ 
    if (arv != NULL){ 
        int i;
        for (i=0; i < MAXFILHOS; i++){
            percorre_pos_ordem(arv->filho[i]);//processa filhos da esquerda para a direita
        }
        checaNo(arv);//só depois processa o nó pai
        percorre_pos_ordem(arv->irmao);
      }
}

// Função que faz a checagem de tipos a partir da árvore sintática
void checaTipos(NoArvore * arv){
    printf("Fazendo Checagem de Tipos...\n");
    percorre_pos_ordem(arv);
    printf("Fim da Checagem de Tipos...\n");
}

//Função que monta a tabela de símbolos a partir da árvore sintática
void montaTabSim(NoArvore * arv){ 
    percorre_pre_ordem(arv);
    if(!possuiMain){
        fprintf(stdout,"\nErro Semântico: Função principal (main) não declarada\n");
        Erro = true;
    }else{
        fprintf(stdout,"\n====================  Tabela de Símbolos  ==================\n\n");
        imprimeTabSim(stdout);
    }
}
