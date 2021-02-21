%{
#define YYPARSER // Diferenciar inclusão do definitions.h
#include <definitions.h>
#define YYSTYPE NoArvore *
//#define YYDEBUG 1
static char * nomeSalvo; // para uso em atribuições
static int numLinhaSalva;
static NoArvore* arvoreSalva; /* armazena árvore para retornar depois */
static int yylex();
int yyerror(char *message);

%}

%token IF ELSE WHILE RETURN INT VOID
%token ID NUM
%token IGUAL IGUALIGUAL DIF MENOR MAIOR MENIGUAL MAIIGUAL MAIS MENOS VEZES DIV ABREPAR FECHAPAR PVIRG VIRG ABRECOL FECHACOL ABRECH FECHACH COMENT ENTER
%token ERROR VAZIO

%% // CFG (Gramática Livre de Contexto) da Linguagem C menos
programa    : decl_lista
                { arvoreSalva = $1;}
            ;
decl_lista  : decl_lista decl
                { YYSTYPE temp = $1;
                // adiciona os nós como irmãos
                // pela recursividade a esquerda
                  if(temp != NULL){
                    while(temp->irmao != NULL)
                        temp = temp->irmao;
                    temp-> irmao = $2;
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
var_decl    : tipo_esp ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
              PVIRG {   $$ = novoNoDecl(D_var);
                        $$->atrib.nome = nomeSalvo;
                        $$->numlinha = numLinhaSalva;
                        $$->tipo = $1;
                    }
            | tipo_esp ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
              ABRECOL NUM FECHACOL PVIRG 
                            { YYSTYPE indice = novoNoExp(E_Num);
                              indice->atrib.val = atoi(tokenString);
                              $$ = novoNoDecl(D_var);
                              $$->filho[0] = indice;
                              $$->tipo = $1;
                              $$->atrib.nome = nomeSalvo;
                            }
            ;
tipo_esp    : INT { Tipo t = Integer; 
                    $$ = t; 
                  } 
            | VOID { Tipo t = Void;
                     $$ = t; 
                   }
            ;
fun_decl    : tipo_esp ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
              ABREPAR params FECHAPAR bloco_decl
              {
                $$ = novoNoDecl(D_func);
                $$->filho[0] = $5;
                $$->filho[1] = $7;
                $$->atrib.nome = nomeSalvo;
                $$->numlinha = numLinhaSalva;
                $$->tipo = $1;
              }
            ;
params      : param_lista { $$ = $1;
                            $$->filho[0] = $1;
                          }
            | VOID {$$ = $1;}
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
param       : tipo_esp ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                   $$ = novoNoExp(E_Id);
                   $$-> atrib.nome = nomeSalvo;
                   $$-> numlinha = numLinhaSalva;
                   $$-> tipo = $1;
                 }
            | tipo_esp ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
              ABRECOL FECHACOL
              {    $$ = novoNoExp(E_Id);
                   $$-> atrib.nome = nomeSalvo;
                   $$-> atrib.eh_vetor = true; // sinaliza que é um vetor
                   $$-> numlinha = numLinhaSalva;
                   $$-> tipo = $1;
              }
            ;
bloco_decl  : ABRECH local_decl stmt_lista FECHACH { $2->irmao = $3;
                                                   $$->$2;
                                                 }                                 
            ;                                     
local_decl  : local_decl var_decl  { YYSTYPE temp = $1;
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
            | VAZIO {   $$ = novoNoExp(E_Id);
                        $$-> atrib.nome = "";
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
            | VAZIO {$$ = $1;}
            ;
stmt        : exp_decl {$$ = $1;}
            | bloco_decl {$$ = $1;}
            | sel_decl {$$ = $1;}
            | iter_decl {$$ = $1;}
            | ret_decl {$$ = $1;}
            ;
exp_decl    : exp PVIRG {$$ = $1;}
            | PVIRG {$$ = NULL;}
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
ret_decl    : RETURN PVIRG {$$ = NULL;}
            | RETURN exp PVIRG {$$ = $2;}
            ;
exp         : var IGUAL exp
                { $$ = novoNoExp(E_Op);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = $2; //IGUAL
                }
            | simples_exp {$$ = $1;}
            ;
var         : ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                   $$ = novoNoExp(E_Id);
                   $$->atrib.nome = nomesalvo;
                   $$->numlinha = numLinhasalva;
                   $$->eh_vetor = true;
                 }
            | ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
            ABRECOL exp FECHACOL
                 { $$ = novoNoExp(E_Id);
                   $$->atrib.nome = nomesalvo;
                   $$->numlinha = numLinhasalva;
                   $$->filho[0] = $4;
                 }
            ;
simples_exp : soma_exp relacional soma_exp
                { $$ = novoNoExp(E_Op);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = $2; // Token recebido pelo relacional
                }
            | soma_exp {$$ = $1;}
            ;
relacional  : MENIGUAL{$$ = $1;}
            | MENOR{$$ = $1;}
            | MAIOR{$$ = $1;}
            | MAIIGUAL{$$ = $1;}
            | IGUALIGUAL{$$ = $1;}
            | DIF{$$ = $1;}
            ;
soma_exp    : soma_exp soma termo
                { $$ = novoNoExp(E_Op);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = $2; // Token recebido pelo "soma"
                }
            | termo {$$ = $1;}
            ;
soma        : MAIS {$$ = $1;}
            | MENOS {$$ = $1;}
            ;
termo       : termo mult fator 
                { $$ = novoNoExp(E_Op);
                  $$->filho[0] = $1;
                  $$->filho[1] = $3;
                  $$->atrib.op = $2; // Token recebido pelo "mult"
                }
            | fator {$$ = $1;}
            ;
mult        : VEZES {$$ = $1;}
            | DIV {$$ = $1;}
            ;
fator       : ABREPAR exp FECHAPAR {$$ = $1;}
            | var {$$ = $1;}
            | ativacao {$$ = $1;}
            | NUM { $$ = novoNoExp(E_Num);
                    indice->atrib.val = atoi(tokenString);
                  }
            ;
ativacao    : ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
            ABREPAR args FECHAPAR
                 { $$->novoNoExp(E_Id);
                   $$->filho[0] = $4;
                   $$->atrib.nome = nomeSalvo;
                   $$->numlinha = numLinhaSalva;
                 }
            ;
args        : arg_lista {$$ = $1;}
            | VAZIO {return NULL;}
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
    //pensar depois se nós precisaremos de um arquivo "listing"...
    fprintf(stderr,"Erro sintático na linha %d!\n mensagem: %s\n",numlinha,message);
    fprintf(stderr,"Token atual: ");
    if(rt == ID || rt == NUM){
        fprintf(stderr,"%s, val= %s\n", nome_token(yychar),yytext);
    }else{
        fprintf(stderr,"%s\n",nome_token(yychar), yytext);
    }
    erro = true;
    return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return retornaToken(); }

TreeNode * parse(void)
{
  extern int yydebug;
 // yydebug = 1;
  //yyparse();
  return arvoreSalva;
}
