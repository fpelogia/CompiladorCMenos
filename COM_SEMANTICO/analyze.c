#include "definitions.h"

//contador para os endereços na lista de blocos
static int location = 0;
static char* escopo = "global";
bool Erro;


// Insere nós na tabela de símbolos 
// Caso já presente, atualiza lista com as linhas
static void insereNo( NoArvore * t){ 
    switch (t->tipo_de_no){
        case TDecl:
            switch (t->tipo.decl){ 
                case D_func:
                    if (consulta_tab_sim(t->atrib.nome) == -1){
                        insere_tab_sim(t->atrib.nome,t->numlinha,location++,"global",t->tipo_c,1);
                        escopo = t->atrib.nome;// escopo da função
                    }else{
                        Erro = 1;
                        printf("Erro Semântico na linha %d\n\tFunção %s já declarada!\n",t->numlinha,t->atrib.nome);
                    }
                    break;
                case D_var: // verificar escopo
                    if (consulta_tab_sim(t->atrib.nome, escopo) == -1)
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
                    if (consulta_tab_sim(t->atrib.nome) == -1){
                        // VERIFICAR TAMBÉM FILTRANDO PELO ESCOPO
                        // TALVEZ ESCREVER FUNÇÃO QUE BUSCA PELO ESCOPO
                        Erro = 1;
                        printf("Erro Semântico na linha %d\n\tFunção %s não declarada no escopo local!\n",t->numlinha,t->atrib.nome);
                    }else
                        insere_tab_sim(t->atrib.nome,t->numlinha,0,escopo,Void,1);//ultimos 4 parâmetros não são utilizados
                    break;
                default:
                     break;
            }
            break;
        case TExp:
            switch (t->tipo.exp){
                case E_Id: // verificar escopo
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
        fprintf(stdout,"Erro sintático na linha %d:\n\t%s\n", t->numlinha, t->atrib.nome);
    else
        fprintf(stdout,"Erro sintático na linha %d:\n\t\n", t->numlinha);
  //Erro = true;
}
/*
// Função que faz checagem de tipo em um dado nó
static void checaNo(NoArvore * t){
    switch (t->tipo_de_no){ 
        case TExp:
            switch (t->tipo.exp){
                case E_Op:
                    if ((t->child[0]->type != Integer) ||(t->child[1]->type != Integer))
                        typeError(t,"Operação aplicada entre não inteiros!");
                    if ((t->attr.op == EQ) || (t->attr.op == LT))
                        t->type = Boolean;
                    else
                        t->type = Integer;
                    break;
                case ConstK:
                case IdK:
                    t->type = Integer;
                    break;
                default:
                    break;
            }
            break;
        case TStmt:
            switch (t->tipo.stmt){
                case IfK:
                    if (t->child[0]->type == Integer)
                        typeError(t->child[0],"if test is not Boolean");
                    break;
                case AssignK:
                    if (t->child[0]->type != Integer)
                        typeError(t->child[0],"assignment of non-integer value");
                    break;
                case WriteK:
                    if (t->child[0]->type != Integer)
                        typeError(t->child[0],"write of non-integer value");
                    break;
                case RepeatK:
                    if (t->child[1]->type == Integer)
                        typeError(t->child[1],"repeat test is not Boolean");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
      }
}*/
// Faz percurso "pré-ordem" em uma árvore inserindo seus
// nós na tabela de símbolos
static void percorre(NoArvore * arv){ 
    if (arv != NULL){ 
        insereNo(arv);//processa nó pai antes dos filhos
        int i;
        for (i=0; i < MAXFILHOS; i++){
            percorre(arv->filho[i]);//processa filhos da esquerda para a direita
        }
        //checaNo(t);
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
    fprintf(stdout,"\nTabela de Símbolos:\n\n");
    imprimeTabSim(stdout);
}
