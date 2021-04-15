#include "definitions.h"

static int tempnum = 1;
static int labelnum = 0;
static int numenderecos = 0;
static int param = 0;
static char* escopo = "global";
static char* nome_var;
static void cGen (NoArvore * arv);

static void genStmt( NoArvore * arv)
{ NoArvore * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc, t1,t2,t3,l1,l2,l3;
  switch (arv->tipo.stmt) {

      case S_If:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         p3 = arv->filho[2] ;
         cGen(p1);//condicao
         t1 = tempnum;
         l1 = labelnum++;
         l2 = labelnum++;
         printf("(IFF, $t%d, L%d,  )\n", t1,l1);
         cGen(p2);// bloco interno
         printf("(GOTO,L%d,  ,  )\n", l2);
         printf("(LAB,L%d,  ,  )\n", l1);
         cGen(p3);// else
         printf("(LAB,L%d,  ,  )\n", l2);
         numenderecos = 0;
         break; 
      case S_While:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         l1 = labelnum++;
         l2 = labelnum++;
         printf("LABEL L%d\n",l1);
         cGen(p1); //condicao
         t1 = tempnum;
         printf("(IFF, $t%d, L%d,  )\n", t1,l2);
         cGen(p2); // loop
         printf("(GOTO,L%d,  ,  )\n", l1);
         printf("LABEL L%d\n",l2);
         break;
      case S_Atrib:
         tempnum++;
         p1 = arv->filho[0];
         p2 = arv->filho[1];
         cGen(p1);
         t1 = tempnum;
         cGen(p2);
         t2 = tempnum;
         printf("(ASSIGN, $t%d, $t%d,  )\n",t1, t2);
         printf("(STORE, %s, $t%d,  )\n",nome_var, t1);
         break;
      case S_Retorno:
         p1 = arv->filho[0];
         cGen(p1);
         printf("(RET, $t%d,  ,  )\n", tempnum++);
         break;
      case S_Chamada:
         p1 = arv->filho[1];
         int npar = 0;
         tempnum++;
         while(p1!= NULL){
            cGen(p1);
            printf("(PARAM, $t%d, ,  )\n", tempnum++);
            p1 = p1->irmao;
            npar++;
         }
         printf("(CALL, %s, %d, $t%d)\n", arv->atrib.nome, npar, tempnum);
         break;
      default:
            break;
    }
}

static void genDecl( NoArvore * arv)
{ NoArvore * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  switch (arv->tipo.decl) {
      case D_Tipo:
         cGen(arv->filho[0]);
         numenderecos = 0;
         break;
      case D_func:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         printf("(FUN,  %s, %s,  )\n", retStrTipo(arv->tipo_c), arv->atrib.nome);
         escopo = arv->atrib.nome;
         param = 1;
         cGen(p1);//args
         param = 0;
         cGen(p2);//corpo
         numenderecos = 0;
         break;
      case D_var:
         if(param == 1){
            printf("(ARG, %s, %s, %s)\n", retStrTipo(arv->tipo_c), arv->atrib.nome, escopo);
         }else{
            printf("(ALLOC, %s, %s,  )\n", arv->atrib.nome,escopo);
         }
         break;

     /* case AssignK:
         if (TraceCode) emitComment("-> assign") ;
         cGen(arv->filho[0]);
         loc = st_lookup(arv->atrib.nome);
         emitRM("ST",ac,loc,gp,"assign: store value");
         if (TraceCode)  emitComment("<- assign") ;
         break; 

      case ReadK:
         emitRO("IN",ac,0,0,"read integer value");
         loc = st_lookup(arv->atrib.nome);
         emitRM("ST",ac,loc,gp,"read: store value");
         break;
      case WriteK:
         cGen(arv->filho[0]);
         emitRO("OUT",ac,0,0,"write ac");
         break;*/
      default:
         break;
    }
} /* genStmt */

static void genExp( NoArvore * arv)
{ int loc;
  NoArvore * p1, * p2;
  switch (arv->tipo.exp) {

    case E_Num :
      tempnum++;
      printf("(LOAD, $t%d, %d,  )\n", tempnum, arv->atrib.val);
      numenderecos++;
      break;
    
    case E_Id :
      tempnum++;
      printf("(LOAD, $t%d, %s,  )\n", tempnum, arv->atrib.nome);
      nome_var = arv->atrib.nome;//perigoso
      numenderecos++;
      break; 

    case E_Op :
         p1 = arv->filho[0];
         p2 = arv->filho[1];
         cGen(p1);
         int t1 = tempnum;
         cGen(p2);
         int t2 = tempnum;
         tempnum++;
         //printf("\n\t\tNUMEND:%d\n", numenderecos);
         switch (arv->atrib.op) {
            case MAIS :
               printf("(ADD, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case MENOS :
               printf("(SUB, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case VEZES :
               printf("(MUL, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case DIV :
               printf("(DIV, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case MENOR :
               printf("(LT, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case IGUALIGUAL :
               printf("(EQUAL, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case DIF :
               printf("(NEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case MENIGUAL:
               printf("(LEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            case MAIIGUAL:
               printf("(GEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               break;
            default:
               //emitComment("BUG: Unknown operator");
               printf("Operador desconhecido\n");
               Erro = 1;
               break;
         } 


         break; 

    default:
      break;
  }
} 

static void cGen( NoArvore * arv)
{ if (arv != NULL)
  { switch (arv->tipo_de_no) {
      case TStmt:
        genStmt(arv);
        break;
      case TExp:
        genExp(arv);
        break;
      case TDecl:
        genDecl(arv);
        break;
      default:
        break;
    }
    cGen(arv->irmao);
  }
}

//gera o código intermediário utilizando a Função
// recursiva cGen, que percorre a arvore sintática
void geraCod(NoArvore * arv){    
    cGen(arv);
    printf("HALT\n\n");
}
