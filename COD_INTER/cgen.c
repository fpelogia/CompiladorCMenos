#include "definitions.h"

static int tempnum = 1;
static int labelnum = 0;
static int numenderecos = 0; //idealmente não passa de 3

static void cGen (NoArvore * arv);

static void genStmt( NoArvore * arv)
{ NoArvore * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  switch (arv->tipo.stmt) {

      case S_If:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         printf("t%d = ",tempnum);
         cGen(p1);
         printf("\n");
         printf("if_f t%d goto L%d\n", tempnum, labelnum);
         numenderecos = 0;
         cGen(p2);
         printf("LABEL L%d\n", labelnum++);
         numenderecos = 0;
         break; 

      case S_While:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         printf("LABEL L%d\n",labelnum);
         cGen(p1);
         break;
      case S_Atrib:
         tempnum++;
         numenderecos++;
         // caso não seja vetor
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         printf("t%d = ", tempnum);
         //printf("\n\t\tNUMEND:%d\n", numenderecos);
         cGen(p2);
         //printf("\n\t\tNUMEND:%d\n", numenderecos);
         printf("\n");
         printf("%s = t%d\n", p1->atrib.nome, tempnum);
         //printf("\n\t\tNUMEND:%d\n", numenderecos);
         numenderecos = 0;
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
      case S_Retorno:
         p1 = arv->filho[0];
         tempnum++;
         printf("t%d = ", tempnum);
         cGen(p1);
         printf("\nreturn t%d\n", tempnum++);
      default:
            break;
    }
} /* genStmt */

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
         p2 = arv->filho[1] ;
         printf("LABEL %s:\n", arv->atrib.nome);
         cGen(p2);
         numenderecos = 0;
         break;
      case D_var:
        /*


        */
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
      printf("%d", arv->atrib.val);
      numenderecos++;
      break;
    
    case E_Id :
      printf("%s", arv->atrib.nome);
      numenderecos++;
      break; 

    case E_Op :
         p1 = arv->filho[0];
         p2 = arv->filho[1];
         cGen(p1);
         //printf("\n\t\tNUMEND:%d\n", numenderecos);
         switch (arv->atrib.op) {
            case MAIS :
               printf("+");
               break;
            case MENOS :
               printf("-");
               break;
            case VEZES :
               printf("*");
               break;
            case DIV :
               printf("/");
               break;
            case MENOR :
               printf("<");
               //emitRO("SUB",ac,ac1,ac,"op <") ;
               //emitRM("JLT",ac,2,pc,"br if true") ;
               //emitRM("LDC",ac,0,ac,"false case") ;
               //emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               //emitRM("LDC",ac,1,ac,"true case") ;
               break;
            case IGUALIGUAL :
               //emitRO("SUB",ac,ac1,ac,"op ==") ;
               printf(" == ");
               //emitRM("JEQ",ac,2,pc,"br if true");
               //emitRM("LDC",ac,0,ac,"false case") ;
               //emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               //emitRM("LDC",ac,1,ac,"true case") ;
               break;
            case DIF :
               //emitRO("SUB",ac,ac1,ac,"op ==") ;
               printf(" != ");
               //emitRM("JEQ",ac,2,pc,"br if true");
               //emitRM("LDC",ac,0,ac,"false case") ;
               //emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               //emitRM("LDC",ac,1,ac,"true case") ;
               break;

            case MENIGUAL:
               printf("<=");
               break;
            case MAIIGUAL:
               printf(">=");
               break;
            default:
               //emitComment("BUG: Unknown operator");
               printf("Operador desconhecido\n");
               Erro = 1;
               break;
         } 

         cGen(p2);

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
