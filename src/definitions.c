#include "definitions.h"

void imprimeTokens(char* nomearq){
    FILE* fc = fopen("sample.c","r");
    if(fc == NULL){
        printf("Falha na leitura do código fonte");
        Erro = 1;
        return;
    }
    char linha[MAX_LINHA];
    bool primeira_vez = true, leftover = false;
    while(1){
        if(fgets(linha, MAX_LINHA, fc) == NULL){
            break;
        }
        if(linha[0] == '\n'){
            if(fgets(linha, MAX_LINHA, fc) == NULL){
                break;
            }
        }

        Token rt;
        int nlsalva;
        if(primeira_vez){
            nlsalva= numlinha + 1;
            primeira_vez = false;
        }else{
            nlsalva = numlinha;
        }
        printf("\n%d: %s", nlsalva, linha);
        if(leftover){
            if(rt == ID || rt == NUM){
                printf("\t%d: %s, val= %s\n",numlinha, nome_token(rt), yytext);
            }else{
                printf("\t%d: %s\n",numlinha, nome_token(rt));
            }
            leftover = false;
        }
        do{
            rt = retornaToken();
            if(rt == EOF ) break;
            else if(numlinha != nlsalva){
                leftover = true;
                
                break;
            }
            if(rt == ID || rt == NUM){
                printf("\t%d: %s, val= %s\n",numlinha, nome_token(rt), yytext);
            }else{
                printf("\t%d: %s\n",numlinha, nome_token(rt));
            }
        }while(1);
    }
    fclose(fc);

}

// Cria e retorna um novo Nó do tipo "Declaração"
NoArvore * novoNoDecl(TipoDecl tipo)
{ NoArvore * no = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (no==NULL)
    fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
    for (i=0;i<MAXFILHOS;i++) no->filho[i] = NULL;
    no->irmao = NULL;
    no->tipo_de_no = TDecl;
    no->tipo.decl = tipo;
    no->numlinha = numlinha;
  }
  return no;
}


// Cria e retorna um novo Nó do tipo "Statement"
NoArvore * novoNoStmt(TipoStmt tipo)
{ NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (t==NULL)
    fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
    for (i=0;i<MAXFILHOS;i++) t->filho[i] = NULL;
    t->irmao = NULL;
    t->tipo_de_no = TStmt;
    t->tipo.stmt = tipo;
    t->numlinha = numlinha;
  }
  return t;
}

// Cria e retorna um novo Nó do tipo "exp"
NoArvore * novoNoExp(TipoExp tipo)
{ NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (t==NULL)
    fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
    for (i=0;i<MAXFILHOS;i++) t->filho[i] = NULL;
    t->irmao = NULL;
    t->tipo_de_no = TExp;
    t->tipo.exp = tipo;
    t->numlinha = numlinha;
  }
  return t;
}

char * copiaString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(stdout,"Sem memória na linha %d\n",numlinha);
  else strcpy(t,s);
  return t;
}

char * retStrTipo(Tipo t){
    if (t == Integer)
        return "int";
    else if( t == Void){
        return "void";
    }else if( t == Array){
        return "int[]";
    }else{
        return "bool";
    }
}


static int indentno = 0;

#define INDENT indentno+=4
#define UNINDENT indentno-=4

static void imprimeEspacos(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(stdout," ");
}

void imprimeArvore( NoArvore * arv )
{ int i;
  INDENT;
  while (arv != NULL) {
    imprimeEspacos();
    if (arv->tipo_de_no==TStmt)
    { switch (arv->tipo.stmt) {
        case S_If:
          fprintf(stdout,"If\n");
          break;
        case S_While:
          fprintf(stdout,"While\n");
          break;
        case S_Atrib:
          fprintf(stdout,"Atribuição\n");
          break;
        case S_Retorno:
          fprintf(stdout,"Retorno\n");
          break;
        case S_Chamada:
          fprintf(stdout,"Chamada da Função %s\n",arv->atrib.nome);
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Stmt\n");
          break;
      }
    }
    else if (arv->tipo_de_no==TExp)
    { switch (arv->tipo.exp) {
        case E_Op:
          fprintf(stdout,"Op:%s\n", nome_token(arv->atrib.op));
          break;
        case E_Num:
          fprintf(stdout,"Num: %d\n",arv->atrib.val);
          break;
        case E_Id:
          // strcmp retorna 0 quando é igual
          if (strcmp(arv->atrib.nome,"void") == 0){
            fprintf(stdout,"void\n");
          }else if(strcmp(arv->atrib.nome,"sem_local_decl") == 0 || strcmp(arv->atrib.nome,"sem_stmt_lista")==0){
            // nada
          }else{
            fprintf(stdout,"Id: %s\n",arv->atrib.nome);
          }
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Exp\n");
          break;
      }
    }else if (arv->tipo_de_no==TDecl)
    { switch (arv->tipo.decl) {
        case D_var:
          fprintf(stdout,"Variável %s\n",arv->atrib.nome);
          break;         
        case D_func:
          //if (arv->tipo_c)
          fprintf(stdout,"Função %s\n",arv->atrib.nome);
          //else  
            //fprintf(stdout,"Função %s com tipo de retorno void \n",arv->atrib.nome, arv->tipo_c);
          break;
        case D_Tipo:
          if (arv->tipo_c == Integer)
            fprintf(stdout,"Tipo int\n");
          else if(arv->tipo_c == Array) 
            fprintf(stdout,"Tipo int[]\n");
          else
            fprintf(stdout,"Tipo void\n");
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Decl\n");
          break;
      }
    }
    else fprintf(stdout,"Tipo desconhecido de Nó\n");
    for (i=0;i<MAXFILHOS;i++){
        imprimeArvore(arv->filho[i]);
    }
    arv = arv->irmao;
  }
  UNINDENT;
}


char* nome_token(Token t){
    char *nome;
    nome = malloc(MAX_TAM_TOKEN*sizeof(char));
    switch(t){
//        case FIMARQ:
  //          strcpy(nome,"fim do arquivo (EOF)");
    //        break;
      //  case ERRO:
        //    strcpy(nome,"Erro !");
          //  break;
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
        case FECHAPAR:
            strcpy(nome,"FECHAPAR");
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
            strcpy(nome, "OUTRO");
            break;
    }
    return nome;
}
//======================================= PILHA ===============================================
void inicializaPilha(Pilha *P){
    P = malloc(sizeof(Pilha*));
    P->numelementos = 0;
    P->topo = NULL;
}

void push(Pilha *P, char* nome){
    TNome *NomeStr = malloc(sizeof(TNome*));
    NomeStr->nome = strdup(nome);
    NomeStr->abaixo = P->topo;
    P->topo = NomeStr;
    P->numelementos ++;
}

char* pop(Pilha *P){
    char *nome = NULL;
    if (P->numelementos != 0){// pilha não vazia
        nome = strdup(P->topo->nome);
        TNome *topoAntigo;
        topoAntigo = P->topo;
        P->topo = topoAntigo->abaixo;
        P->numelementos --;
        nome = strdup(topoAntigo->nome);
        free(topoAntigo);
    }
    return nome;
}

// =========================== LISTA DE QUADRUPLAS ===============================

void inicializaListaQuad(ListaQuad *lq){
    lq->prim = NULL;
}

void insereQuad(ListaQuad *lq, char *op, char *c1, char *c2, char *c3){
    NoQuad *novoNoQ = malloc(sizeof(NoQuad*));
    Quad *novaQ = malloc(sizeof(Quad*));
    novaQ->op = strdup(op);
    novaQ->c1 = strdup(c1);
    novaQ->c2 = strdup(c2);
    novaQ->c3 = strdup(c3);
    novoNoQ->quad = novaQ;
    novoNoQ->prox = NULL;
    
    if(lq->prim != NULL){
        NoQuad* lq_p = lq->prim;
        while(lq_p->prox != NULL){
            lq_p = lq_p->prox;
            //lq_p->prox = novoNoQ;
        }
        lq_p->prox = novoNoQ;
    }else{
        lq->prim = novoNoQ;
    }
}

void imprimeListaQuad(ListaQuad *lq){
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        lq_p = lq_p->prox;
    }
    printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
}

void percorreListaQuad(ListaQuad *lq){
    printf("\n=============== Código Assembly ==================\n\n");
    NoQuad* lq_p = lq->prim;
    while(lq_p->prox != NULL){
        //printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
        if(eh_operacao(lq_p->quad->op))   gera_asm_R(lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);        
        if(strcmp(lq_p->quad->op, "LOAD") == 0){
            gera_asm_R_LOAD(lq_p->quad->c1, lq_p->quad->c2);
        }
        lq_p = lq_p->prox;
    }
    //printf("(%s,%s,%s,%s)\n",lq_p->quad->op, lq_p->quad->c1, lq_p->quad->c2, lq_p->quad->c3);
}

void gera_asm_R_LOAD(char* c1, char* c2){
    if((c2[0] >= 48) && (c2[0] <= 57)){
        // campo 2 é um número
        printf("addi $%s, $t0, %s\n", c1, c2);
    }else{
        // campo 2 é o nome de uma variável
        // [TODO]: no futuro trocar fp pelo número do reg.
        printf("lw $%s, $fp(%d)\n", c1, var_id(c2));
    }
}

int var_id(char * var_name){
    return 1;
}
void gera_asm_R(char* op, char* c1, char* c2, char* c3){
    if(strcmp(op, "ADD") == 0){
        printf("\t\t\t\tadd $%s, $%s, $%s\n", c3, c1, c2);
    }
    if(strcmp(op, "SUB") == 0){
        printf("\t\t\t\tsub $%s, $%s, $%s\n", c3, c1, c2);
    }
    if(strcmp(op, "MUL") == 0){
        printf("\t\t\t\tmul $%s, $%s, $%s\n", c3, c1, c2);
    }
    if(strcmp(op, "DIV") == 0){
        printf("\t\t\t\tdiv $%s, $%s, $%s\n", c3, c1, c2);
    }
}

int eh_operacao(char* op){
    return strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0  || strcmp(op, "MUL") == 0 || strcmp(op, "DIV") == 0 ;
}
