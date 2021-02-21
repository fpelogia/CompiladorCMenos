#include "definitions.h"

char tokenString[MAX_TAM_TOKEN + 1];

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
    no->tipo.stmt = tipo;
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
    t->tipo_c = Void;
  }
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void imprimeEspacos(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(stdout," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
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
        case S_Params:
          fprintf(stdout,"Params\n");
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Stmt\n");
          break;
      }
    }
    else if (arv->tipo_de_no==TExp)
    { switch (arv->tipo.exp) {
        case E_Op:
          fprintf(stdout,"Op: ");
          //printToken(arv->atrib.op,"\0");
          printf("%s", nome_token(arv->atrib.op));
          break;
        case E_Num:
          fprintf(stdout,"Num: %d\n",arv->atrib.val);
          break;
        case E_Id:
          fprintf(stdout,"Id: %s\n",arv->atrib.nome);
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Exp\n");
          break;
      }
    }else if (arv->tipo_de_no==TDecl)
    { switch (arv->tipo.decl) {
        case D_var:
          fprintf(stdout,"Declaração da Variável %s do tipo %d\n",arv->atrib.nome, arv->tipo);
          //printToken(arv->atrib.op,"\0");
          //printf("%s", nome_token(arv->atrib.op));
          break;
        case D_func:
          fprintf(stdout,"Declaração da Função %s com tipo de retorno %d \n",arv->atrib.nome, arv->tipo);
          break;
        default:
          fprintf(stdout,"Tipo desconhecido de Decl\n");
          break;
      }
    }

    else fprintf(stdout,"Tipo desconhecido de Nó\n");
    for (i=0;i<MAXFILHOS;i++)
         imprimeArvore(arv->filho[i]);
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

