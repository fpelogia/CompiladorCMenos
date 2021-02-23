#include "globals.h"
#include "symtab.h"
#include "analyze.h"

//contador para os endereços na lista de blocos
static int location = 0;

// Faz percurso "pré-ordem" em uma árvore inserindo seus
// nós na tabela de símbolos
static void percorre(NoArvore * arv){ 
    if (arv != NULL){ 
        insereNo(t);//processa nó pai antes dos filhos
        int i;
        for (i=0; i < MAXFILHOS; i++){
            percorre(arv->filho[i]);//processa filhos da esquerda para a direita
        }
        percorre(t->irmao);
      }
}

// Insere nós na tabela de símbolos 
// Caso já presente, atualiza lista com as linhas
static void insereNo( NoArvore * t){ 
    switch (t->tipo_de_no){
        case TDecl:
            switch (t->tipo.decl){ 
                case D_var:
                case D_func:
                    if (consulta_tab_sim(t->atrib.nome) == -1)
                        insere_tab_sim(t->atrib.nome,t->numlinha,location++);
                    else
                        insere_tab_sim(t->atrib.nome,t->numlinha,0);
                    break;
                default:
                     break;
            }
            break;
        case TStmt:
            switch (t->tipo.stmt){ 
                case S_Chamada:
                    if (consulta_tab_sim(t->atrib.nome) == -1)
                        insere_tab_sim(t->atrib.nome,t->numlinha,location++);
                    else
                        insere_tab_sim(t->atrib.nome,t->numlinha,0);
                    break;
                default:
                     break;
            }
            break;
        case TExp:
            switch (t->tipo.exp){
                case E_Id:
                    if (consulta_tab_sim(t->atrib.nome) == -1)
                        insere_tab_sim(t->atrib.nome,t->numlinha,location++);
                    else
                        insere_tab_sim(t->atrib.nome,t->numlinha,0);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

//Função que monta a tabela de símbolos a partir da árvore sintática
void montaTabSim(NoArvore * arv){ 
    percorre(arv);
    fprintf(stdout,"\nTabela de Símbolos:\n\n");
    imprimeTabSim(stdout);
}

static void typeError(NoArvore * t, char * message){
    if(t->atrib.nome)
        fprintf(listing,"Erro sintático:%s na linha %d: %s\n", t->atrib.nome, t->numlinha);
    else
        fprintf(listing,"Erro sintático na linha %d: %s\n", t->numlinha);
  //Erro = true;
}

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
}

// Função que faz a checagem de tipos a partir da árvore sintática
void checaTipos(NoArvore * arv){
    percorre(arv,nullProc,checkNode);
}
