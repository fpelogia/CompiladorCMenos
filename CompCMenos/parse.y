%{
#define YYPARSER // Diferenciar inclusão do definitions.h
#include "definitions.h"
#define YYSTYPE NoArvore *
//#define YYDEBUG 1
static char * nomeSalvo; // para uso geral em IDs
static char * nomeVarSalvo; // para uso em atribuições
static char * nomeFuncDecl; // para uso em declaracao de funções
static char * nomeFunc; // para uso em funções
static int numLinhaSalva;
static int numLinhaSalvaF;
static NoArvore* arvoreSalva; /* armazena árvore para retornar depois */
static int yylex();
int yyerror(char *message);

%}

%token IF ELSE WHILE RETURN INT VOID
%token ID NUM
%token IGUAL IGUALIGUAL DIF MENOR MAIOR MENIGUAL MAIIGUAL MAIS MENOS VEZES DIV ABREPAR FECHAPAR PVIRG VIRG ABRECOL FECHACOL ABRECH FECHACH COMENT ENTER
%token ERRO FIMARQ ESPACO

%% // CFG (Gramática Livre de Contexto) da Linguagem C menos
programa    : decl_lista
                { arvoreSalva = $1;}
            ;
decl_lista  : decl_lista decl
                { YYSTYPE temp = $1;
                // adiciona os nós como irmãos
                // pela recursividade a esquerda
                  if(temp != NULL){
                    while(temp->filho[0]->irmao != NULL)
                        temp = temp->filho[0]->irmao;
                    temp->filho[0]->irmao = $2;
                    $$ = $1;
                  }else{
                    $$ = $2;
                  }
                }   
            | decl {$$ = $1;}
            ;
decl        : var_decl {$$ = $1;}
            | fun_decl {$$ = $1;}
            ;
var_decl    : tipo_esp ID { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
              PVIRG {   $$ = $1;
                        YYSTYPE vd;
                        vd = novoNoDecl(D_var);
                        vd->atrib.nome = nomeSalvo;
                        vd->numlinha = numLinhaSalva;
                        vd->tipo_c = $1->tipo_c;
                        $$->filho[0] = vd;
                    }
            | tipo_esp ID { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
              ABRECOL NUM FECHACOL PVIRG 
                            { $$ = $1;
                              YYSTYPE indice = novoNoExp(E_Num);
                              indice->atrib.val = atoi(NUM_val);
                              indice->tipo_c = Integer;
                              YYSTYPE vd;
                              vd = novoNoDecl(D_var);
                              vd->atrib.nome = nomeSalvo;
                              vd->numlinha = numLinhaSalva;
                              vd->filho[0] = indice;
                              if($1->tipo_c == Integer)
                                vd->tipo_c = Array;
                              else
                                vd->tipo_c = Void;
                              $$->filho[0] = vd; //nó de tipo fica como pai da declaracao
                            }
            ;
tipo_esp    : INT { $$ = novoNoDecl(D_Tipo); // cria o nó para o tipo
                    $$->tipo_c = Integer; 
                  } 
            | VOID { $$ = novoNoDecl(D_Tipo); // cria o nó para o tipo
                    $$->tipo_c = Void; 
                   }
            ;
fun_decl    : tipo_esp ID {
                    nomeFuncDecl = copiaString(ID_nome);
                    numLinhaSalvaF = numlinha;
                 }
              ABREPAR params FECHAPAR bloco_decl
              {
                $$ = $1;
                YYSTYPE fun;
                fun = novoNoDecl(D_func);
                fun->filho[0] = $5;
                fun->filho[1] = $7;
                fun->atrib.nome = nomeFuncDecl;
                fun->numlinha = numLinhaSalvaF;
                fun->tipo_c = $1->tipo_c;
                $$->filho[0] = fun;
              }
            ;
params      : param_lista { $$ = $1;
                            //$$->filho[0] = $1;
                          }
            | VOID { $$ = novoNoExp(E_Id); $$->atrib.nome = "void"; $$->tipo_c = Void;}
            ;
param_lista : param_lista VIRG param {  YYSTYPE temp = $1;
                                        // adiciona os nós como irmãos
                                        if(temp != NULL){
                                            while(temp->irmao != NULL){
                                                temp = temp->irmao;
                                            }
                                            temp-> irmao = $3;
                                            $$ = $1;
                                        }else{
                                            $$ = $3;
                                        }
                                     }
            | param {$$ = $1;}
            ;
param       : tipo_esp ID { 
                   $$ = $1;
                   nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                   YYSTYPE par;
                   par = novoNoDecl(D_var); // cuidado com isso
                   par-> atrib.nome = nomeSalvo;
                   par-> numlinha = numLinhaSalva;
                   par-> tipo_c = $1->tipo_c;
                   $$->filho[0] = par;
                 }
            | tipo_esp ID {nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
              ABRECOL FECHACOL
              {    $$ = $1;
                   YYSTYPE par;
                   par = novoNoDecl(D_var);
                   par-> atrib.nome = nomeSalvo;
                   par-> numlinha = numLinhaSalva;
                   if($1->tipo_c == Integer){
                      par-> tipo_c = Array;
                   }else{
                      par->tipo_c = $1->tipo_c;
                   }
                   $$->filho[0] = par;
              }
            ;
bloco_decl  : ABRECH local_decl stmt_lista FECHACH { { YYSTYPE temp = $2;
                                                    // adiciona os nós como irmãos
                                                      if(temp != NULL){
                                                        while(temp->irmao != NULL){
                                                            temp = temp->irmao;
                                                        }
                                                        temp-> irmao = $3;
                                                        $$ = $2;
                                                      }else{
                                                        $$ = $3;
                                                      }
                                                    }      
                                                   } 
            ;                                     
local_decl  : local_decl var_decl  { YYSTYPE temp = $1;
                                    // adiciona os nós como irmãos
                                      if(temp != NULL && temp->atrib.nome != "sem_local_decl" ){
                                        while(temp->irmao != NULL){
                                            temp = temp->irmao;
                                        }
                                        temp-> irmao = $2;
                                        $$ = $1;
                                      }else{
                                        $$ = $2;
                                      }
                                    }   
            |/*vazio*/{ 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_local_decl";
                        $$ = NULL;
                    }
            ;
stmt_lista  : stmt_lista stmt { YYSTYPE temp = $1;
                                    // adiciona os nós como irmãos
                                      if(temp != NULL){
                                        while(temp->irmao != NULL){
                                            temp = temp->irmao;
                                        }
                                        temp-> irmao = $2;
                                        $$ = $1;
                                      }else{
                                        $$ = $2;
                                      }
                                    }   
            |/*vazio*/{ 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_stmt_lista";
                        $$ = NULL;
                    }
            ;
stmt        : exp_decl {$$ = $1;}
            | bloco_decl {$$ = $1;}
            | sel_decl {$$ = $1;}
            | iter_decl {$$ = $1;}
            | ret_decl {$$ = $1;}
            ;
exp_decl    : exp PVIRG {$$ = $1;}
            | PVIRG { 
                        //$$ = novoNoExp(E_Id);
                        //$$->atrib.nome = "expr_vazia";
                        $$ = NULL;
                    }
            ;
sel_decl    : IF ABREPAR exp FECHAPAR stmt
                { $$ = novoNoStmt(S_If);
                  $$->filho[0] = $3;
                  $$->filho[1] = $5;
                }
            | IF ABREPAR exp FECHAPAR stmt ELSE stmt
                { $$ = novoNoStmt(S_If);
                  $$->filho[0] = $3;
                  $$->filho[1] = $5;
                  $$->filho[2] = $7;
                }
            ;
iter_decl   : WHILE ABREPAR exp FECHAPAR stmt
                { $$ = novoNoStmt(S_While);
                  $$->filho[0] = $3;
                  $$->filho[1] = $5;
                }
            ;
ret_decl    : RETURN PVIRG { 
                        $$ = novoNoStmt(S_Retorno);
                    }    
            | RETURN exp PVIRG {$$ = novoNoStmt(S_Retorno);
                                $$->filho[0] = $2;
                                }
            ;
exp         : var IGUAL exp
                { $$ = novoNoStmt(S_Atrib);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = IGUAL; //IGUAL
                }
            | simples_exp {$$ = $1;}

            ;
var         : ID { nomeSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                   $$ = novoNoExp(E_Id);
                   $$->atrib.nome = nomeSalvo;
                   $$->numlinha = numLinhaSalva;
                   $$->tipo_c = Void;// precisa buscar na TS
                 }
            | ID { nomeVarSalvo = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
            ABRECOL exp FECHACOL
                 {
                   $$ = novoNoExp(E_Id);
                   $$->atrib.nome = nomeVarSalvo;
                   $$->numlinha = numLinhaSalva;
                   $$->filho[0] = $4;
                   $$->tipo_c = Integer; //certeza. v[indice] é inteiro
                 }
            ;
simples_exp : soma_exp relacional soma_exp
                { $$ = novoNoExp(E_Op);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = $2->atrib.op; // Token recebido pelo relacional
                }
            | soma_exp {$$ = $1;}
            ;
relacional  : MENIGUAL{$$ = novoNoExp(E_Id); $$->atrib.op = MENIGUAL;}
            | MENOR{$$ = novoNoExp(E_Id); $$->atrib.op = MENOR;}
            | MAIOR{$$ = novoNoExp(E_Id); $$->atrib.op = MAIOR;}
            | MAIIGUAL{$$ = novoNoExp(E_Id); $$->atrib.op = MAIIGUAL;}
            | IGUALIGUAL{$$ = novoNoExp(E_Id); $$->atrib.op = IGUALIGUAL;}
            | DIF{$$ = novoNoExp(E_Id); $$->atrib.op = DIF;}
            ;
soma_exp    : soma_exp soma termo
                { $$ = novoNoExp(E_Op);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = $2->atrib.op; // Token recebido pelo "soma"
                }
            | termo {$$ = $1;}
            ;
soma        : MAIS {$$ = novoNoExp(E_Id); $$->atrib.op = MAIS;}
            | MENOS {$$ = novoNoExp(E_Id); $$->atrib.op = MENOS;}

            ;
termo       : termo mult fator 
                { $$ = novoNoExp(E_Op);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = $2->atrib.op; // Token recebido pelo "mult"
                }
            | fator {$$ = $1;}
            ;
mult        : VEZES {$$ = novoNoExp(E_Id); $$->atrib.op = VEZES;}
            | DIV {$$ = novoNoExp(E_Id); $$->atrib.op = DIV;}
            ;
fator       : ABREPAR exp FECHAPAR {$$ = $1;}
            | var {$$ = $1;}
            | ativacao {$$ = $1;}
            | NUM { $$ = novoNoExp(E_Num);
                    $$->atrib.val = atoi(NUM_val);
                    $$->tipo_c = Integer;
                  }
            ;
ativacao    : ID { nomeFunc = copiaString(ID_nome);
                   numLinhaSalva = numlinha;
                 }
            ABREPAR args FECHAPAR
                 { $$ = novoNoStmt(S_Chamada);
                   $$->filho[1] = $4; // filho direito
                   $$->atrib.nome = nomeFunc;
                   $$->numlinha = numLinhaSalva;
                 }
            ;
args        : arg_lista {$$ = $1;}
            |/*vazio*/{ 
                        //$$ = novoNoExp(E_Id);
                        //$$-> atrib.nome = "sem_args";
                        $$ = NULL;
                    }
            ;
arg_lista   : arg_lista VIRG exp {  YYSTYPE temp = $1;
                                    // adiciona os nós como irmãos
                                    if(temp != NULL){
                                        while(temp->irmao != NULL){
                                            temp = temp->irmao;
                                        }
                                        temp-> irmao = $3;
                                        $$ = $1;
                                    }else{
                                        $$ = $3;
                                    }
                                 }
            | param {$$ = $1;}
            | exp {$$ = $1;}
            ;
%%

int yyerror(char * message){
    if(yychar == ID || yychar == NUM){
        fprintf(stdout,"Erro Sintático %s  na linha: %d\n", nome_token(yychar), numlinha);
    }else{
        fprintf(stdout,"Erro Sintático %s (%s)  na linha: %d\n", nome_token(yychar), yytext, numlinha);
    }
    Erro = true;
    return 0;
}

// Informa ao Yacc a função reponsável pela análise léxica 
static int yylex(void)
{ return retornaToken(); }

// Função principal do analisador sintático
NoArvore * parse(void){
//  extern int yydebug;
//  yydebug = 1;
  yyparse();
  return arvoreSalva;
}
