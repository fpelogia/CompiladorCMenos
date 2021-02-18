%{
#define YYPARSER // Diferenciar inclusão do definitions.h
#include <stdio.h>
#include <definitions.h>
#define YYSTYPE NoArvore *
//#define YYDEBUG 1
static char * nomeSalvo; // para uso em atribuições
static int numLinhaSalva;
static Tipo tipoSalvo; //para declaracoes de variavel
static NoArvore* arvoreSalva; /* armazena árvore para retornar depois */
static int yylex();
int yyerror(char *message);

%}

%token IF ELSE WHILE RETURN INT VOID
%token ID NUM
%token IGUAL IGUALIGUAL DIF MENOR MAIOR MENIGUAL MAIIGUAL MAIS MENOS VEZES DIV ABREPAR FECHAPAR PVIRG VIRG ABRECOL FECHACOL ABRECH FECHACH COMENT ENTER
%token ERROR

%% // CFG (Gramática Livre de Contexto) da Linguagem C menos
programa    : decl_lista
                { arvoreSalva = $1;}
            ;
decl_lista  : decl_lista decl
                { YYSTYPE temp = $1;
                // adiciona os nós como irmãos
                // pela recursividade a esquerda
                  if(temp != NULL){
                    while(temp->irmao != NULL){
                        temp = temp->irmao;
                    }
                    temp-> irmao = $2;
                    $$ = $1;
                  }else{
                    $$ = $3;
                  }
                }   
            | decl {$$ = $1;}
            ;
decl        : var_decl {$$ = $1}
            | fun_decl
            ;
var_decl    : tipo_esp { if($1==INT)
                            tipoSalvo = Integer;
                         else if($1==VOID)
                            tipoSalvo = Void;
                         else
                            erro = true;
                       }
              ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
              PVIRG {   $$ = novoNoDecl(D_var);
                        $$->atrib.nome = nomeSalvo;
                        $$->numlinha = numlinhaSalva;
                        $$->tipo = tipoSalvo;
                    }
            | tipo_esp { if($1==INT)
                            tipoSalvo = Integer;
                         else if($1==VOID)
                            tipoSalvo = Void;
                         else
                            erro = true;
                       }
              ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
              ABRECOL NUM FECHACOL PVIRG
              /* PENSAR EM COMO LIDAR COM O [NUM]*/
            ;
tipo_esp    : INT { $$ = $1; } 
            | VOID { $$ = $1; }
            ;
fun_decl    : tipo_esp { if($1==INT)
                            tipoSalvo = Integer;
                         else if($1==VOID)
                            tipoSalvo = Void;
                         else
                            erro = true;
                       }
              ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }
                 
              ABREPAR params FECHAPAR bloco_decl
              {
                $$ = novoNoDecl(D_func);
                $$->filho[0] = $6;
                $$->filho[1] = $8;
                $$->atrib.nome = nomeSalvo;
                $$->numlinha = numLinhaSalva;
                $$->tipo = tipoSalvo;
              }

            ;
params      : param_lista {$$ = $1;}
            | VOID {$$ = $1;}
            ;
param_lista : param_lista VIRG param {  
                                       $$ = novoNoStmt(S_Params);
                                       $$->filho[0] = $1;
                                       $$->filho[1] = $3;
                                       /* Isso não me cheira bem*/
                                     }
            | param {$$ = $1;}
            ;
param       : tipo_esp { if($1==INT)
                            tipoSalvo = Integer;
                         else if($1==VOID)
                            tipoSalvo = Void;
                         else
                            erro = true;
                       }
              ID { strcpy(nomeSalvo, tokenString);
                   numLinhaSalva = numlinha;
                 }

            | tipo_esp ID ABRECOL FECHACOL
            ;
bloco_decl  : ABRECH local_decl var_decl 
            | vazio
local_decl  : local_decl var_decl
            | vazio
            ;
stmt_lista  : stmt_lista stmt 
            | vazio
            ;
stmt        : exp_decl 
            | bloco_decl
            | sel_decl
            | iter_decl
            | ret_decl
            ;
exp_decl    : exp PVIRG
            | PVIRG
            ;
sel_decl    : IF ABREPAR exp FECHAPAR stmt
            | IF ABREPAR exp FECHAPAR stmt ELSE stmt
            ;
iter_decl   : WHILE ABREPAR exp FECHAPAR stmt
            ;
ret_decl    : RETURN PVIRG
            | RETURN exp PVIRG
            ;
exp         : var IGUAL exp
            | simples_exp
            ;
var         : ID
            | ID ABRECOL exp FECHACOL
            ;
simples_exp : soma_exp relacional soma_exp
            | soma_exp
            ;
relacional  : MENIGUAL
            | MENOR
            | MAIOR
            | MAIIGUAL
            | IGUALIGUAL
            | DIF
            ;
soma_exp    : soma_exp soma termo
            | termo
            ;
soma        : MAIS
            | MENOS
termo       : termo mult fator 
            | fator
            ;
mult        : VEZES
            | DIV
            ;
fator       : ABREPAR exp FECHAPAR
            | var 
            | ativacao
            | NUM
            ;
ativacao    : ID ABREPAR args FECHAPAR
            ;
args        : arg_lista 
            | vazio
            ;
arg_lista   : arg_lista VIRG exp
            | exp
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
  //extern int yydebug;
  //yydebug = 1;
  yyparse();
  return arvoreSalva;
}
