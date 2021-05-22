#include "definitions.h"

static int tempnum = 1;
static int labelnum = 0;
static int param = 0;
static char* param_list[500]; // Máximo de 500 parâmetros
static int param_list_size = 0;
static bool nao_avance_irmao = false;
static char* escopo = "global";
static Pilha nome_var_pilha;
static void cGen (NoArvore * arv);
ListaQuad CodInter;

char* treg ( int num ){
    char* tr = malloc(4*sizeof(char));
    sprintf(tr,"t%d",num);
    return tr;
}

char* lnum ( int num ){
    char* ln = malloc(5*sizeof(char)); 
    sprintf(ln,"L%d",num);
    return ln;
}

char* numtostr( int num ){
    int num_orig = num;
    if(num == 0){
        char* ns = malloc(2*sizeof(char)); 
        ns[0] = '0';
        ns[1] = '\0';
        return ns;
    }
    int ndig = 0;
    //contagem de dígitos
    while (num != 0) {
        num /= 10;
        ndig++;
    }
    char* ns = malloc((ndig+1)*sizeof(char)); 
    sprintf(ns,"%d",num_orig);
    return ns;
}

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
         //printf("(IFF, $t%d, L%d,  )\n", t1,l1);
         insereQuad(&CodInter,"IFF", treg(t1), lnum(l1)," ");
         cGen(p2);// bloco interno
         //printf("(GOTO,L%d,  ,  )\n", l2);
         insereQuad(&CodInter,"GOTO",lnum(l2), " ", " ");
         //printf("(LAB,L%d,  ,  )\n", l1);
         insereQuad(&CodInter,"LAB",lnum(l1), " ", " ");
         cGen(p3);// else
         //printf("(LAB,L%d,  ,  )\n", l2);
         insereQuad(&CodInter,"LAB",lnum(l2), " ", " ");
         break; 
      case S_While:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         l1 = labelnum++;
         l2 = labelnum++;
         //printf("LABEL L%d\n",l1);
         insereQuad(&CodInter,"LABEL",lnum(l1), " ", " ");
         cGen(p1); //condicao
         t1 = tempnum;
         //printf("(IFF, $t%d, L%d,  )\n", t1,l2);
         insereQuad(&CodInter,"IFF",treg(t1),lnum(l2), " ");
         cGen(p2); // loop
         //printf("(GOTO,L%d,  ,  )\n", l1);
         insereQuad(&CodInter,"GOTO",lnum(l1)," ", " ");
         //printf("LABEL L%d\n",l2);
         insereQuad(&CodInter,"LABEL",lnum(l2), " ", " ");
         break;
      case S_Atrib:
         tempnum++;
         p1 = arv->filho[0];
         p2 = arv->filho[1];
         push(&nome_var_pilha, p1->atrib.nome);
         cGen(p1);
         t1 = tempnum;
         cGen(p2);
         t2 = tempnum;
         //printf("(ASSIGN, $t%d, $t%d,  )\n",t1, t2);
         insereQuad(&CodInter,"ASSIGN", treg(t1), treg(t2), " ");
         char *nome_var = pop(&nome_var_pilha);
         //printf("(STORE, %s, $t%d,  )\n",nome_var, t1);
         insereQuad(&CodInter,"STORE",nome_var, treg(t1), " ");
         break;
      case S_Retorno:
         p1 = arv->filho[0];
         cGen(p1);
         //printf("(RET, $t%d,  ,  )\n", tempnum++);
         insereQuad(&CodInter, "RET", treg(tempnum++), " ", " ");
         break;
      case S_Chamada:
         p1 = arv->filho[1];
         int npar = 0;
         tempnum++;
         nao_avance_irmao = true;
         while(p1!= NULL){
            cGen(p1);
            //printf("(PARAM, $t%d, ,  )\n", tempnum++);
            insereQuad(&CodInter, "PARAM", treg(tempnum++), " ", " ");
            p1 = p1->irmao;
            npar++;
         }
         nao_avance_irmao = false;
         //printf("(CALL, %s, %d, $t%d)\n", arv->atrib.nome, npar, tempnum);
         insereQuad(&CodInter, "CALL", arv->atrib.nome, numtostr(npar), treg(tempnum));
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
         break;
      case D_func:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         //printf("(FUN,  %s, %s,  )\n", retStrTipo(arv->tipo_c), arv->atrib.nome);
         insereQuad(&CodInter, "FUN",retStrTipo(arv->tipo_c), arv->atrib.nome, " ");
         escopo = arv->atrib.nome;
         param = 1;
         cGen(p1);//args
         //loads dos args
         int i;
         for (i=0;i<param_list_size;i++){
            insereQuad(&CodInter, "LOAD",treg(tempnum++), param_list[i], " ");
         }
         param = 0;
         cGen(p2);//corpo
         //printf("(END,  %s,  ,  )\n",arv->atrib.nome);
         insereQuad(&CodInter, "END",arv->atrib.nome, " ", " ");
         param_list_size = 0;
         break;
      case D_var:
         if(param == 1){
            //printf("(ARG, %s, %s, %s)\n", retStrTipo(arv->tipo_c), arv->atrib.nome, escopo);
            insereQuad(&CodInter, "ARG", retStrTipo(arv->tipo_c), arv->atrib.nome, escopo);
            param_list[param_list_size++] = strdup(arv->atrib.nome);
            
         }else{
            if(arv->filho[0] != NULL){
                //printf("(ALLOC, %s, %s, %d)\n", arv->atrib.nome, escopo, arv->filho[0]->atrib.val);
                insereQuad(&CodInter, "ALLOC", arv->atrib.nome, escopo, numtostr(arv->filho[0]->atrib.val));  
            }else{
                //printf("(ALLOC, %s, %s,  )\n", arv->atrib.nome, escopo);
                insereQuad(&CodInter, "ALLOC", arv->atrib.nome, escopo, " ");
            }
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
      //printf("(LOAD, $t%d, %d,  )\n", tempnum, arv->atrib.val);
      insereQuad(&CodInter, "LOAD", treg(tempnum), numtostr(arv->atrib.val), " ");
      break;
    
    case E_Id :
      if(strcmp(arv->atrib.nome, "void")==0)   break;
      if(arv->filho[0] != NULL){
        cGen(arv->filho[0]);
        int t1 = tempnum;
        tempnum++;
        //printf("(MUL, $t%d, 4, $t%d )\n", t1, tempnum);
        insereQuad(&CodInter, "MUL", treg(t1), "4", treg(tempnum));
        tempnum++;
        //printf("(LOAD, $t%d, %s, $t%d )\n", tempnum, arv->atrib.nome, tempnum-1);
        insereQuad(&CodInter, "LOAD", treg(tempnum), arv->atrib.nome, treg(tempnum-1));
      }else{
        tempnum++;
        //printf("(LOAD, $t%d, %s,  )\n", tempnum, arv->atrib.nome);
        insereQuad(&CodInter, "LOAD", treg(tempnum), arv->atrib.nome, " ");
      }
      break; 

    case E_Op :
         p1 = arv->filho[0];
         p2 = arv->filho[1];
         cGen(p1);
         int t1 = tempnum;
         cGen(p2);
         int t2 = tempnum;
         tempnum++;
         switch (arv->atrib.op) {
            case MAIS :
               //printf("(ADD, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "ADD", treg(t1), treg(t2), treg(tempnum));
               break;
            case MENOS :
               //printf("(SUB, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "SUB", treg(t1), treg(t2), treg(tempnum));
               break;
            case VEZES :
               //printf("(MUL, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "MUL", treg(t1), treg(t2), treg(tempnum));
               break;
            case DIV :
               //printf("(DIV, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "DIV", treg(t1), treg(t2), treg(tempnum));
               break;
            case MENOR :
               //printf("(LT, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "LT", treg(t1), treg(t2), treg(tempnum));
               break;
            case MAIOR :
               //printf("(GT, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "GT", treg(t1), treg(t2), treg(tempnum));
               break;
            case IGUALIGUAL :
               //printf("(EQUAL, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "EQUAL", treg(t1), treg(t2), treg(tempnum));
               break;
            case DIF :
               //printf("(NEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "NEQ", treg(t1), treg(t2), treg(tempnum));
               break;
            case MENIGUAL:
               //printf("(LEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "LEQ", treg(t1), treg(t2), treg(tempnum));
               break;
            case MAIIGUAL:
               //printf("(GEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               insereQuad(&CodInter, "GEQ", treg(t1), treg(t2), treg(tempnum));
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
    if(nao_avance_irmao == false){
        cGen(arv->irmao);
    }
  }else{
    Erro = true;    
  }
}

//gera o código intermediário utilizando a Função
// recursiva cGen, que percorre a arvore sintática
void geraCod(NoArvore * arv){    
    inicializaPilha(&nome_var_pilha);
    cGen(arv);
    //printf("(HALT, , , )\n\n");
    insereQuad(&CodInter, "HALT", " ", " ", " ");
    imprimeListaQuad(&CodInter);
}
