%{
#define YYPARSER // Diferenciar inclusão do definitions.h
#include <stdio.h>
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
%token ERROR

%% // CFG (Gramática Livre de Contexto) da Linguagem C menos
programa    : decl_lista
            ;
decl_lista  : decl_lista decl   
            | decl
            ;
decl        : var_decl
            | fun_decl
            ;
var_decl    : tipo_esp ID PVIRG
            | tipo_esp ID ABRECOL NUM FECHACOL PVIRG
            ;
tipo_esp    : INT 
            | VOID
            ;
fun_decl    : tipo_esp ID ABREPAR params FECHAPAR bloco_decl
            ;
params      : param_lista VIRG param 
            | param
            ;
param       : tipo_esp ID | tipo_esp ID ABRECOL FECHACOL
            ;
bloco_decl  : '{' local_decl var_decl 
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

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
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
