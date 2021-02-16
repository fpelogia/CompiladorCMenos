%{
#include "definitions.h"
%}
DIGITO [0-9]
LETRA [a-zA-Z]
ESPACO [ \t]+
ENTER \n
%%
"/*"    { char c;
           int ast = 0;
          do
          { c = input();
            if (c == EOF) break;
            //if (c == '\n') numlinha++;
            if(c == '*'){
                ast = 1;
            }
          } while (ast != 1 || c != '/');
        }
"else" { return ELSE;}
"if" { return IF;}
"int" { return INT;}
"return" { return RETURN;}
"void" { return VOID;}
"while" { return WHILE;}
{LETRA}({LETRA}|{DIGITO})* {return ID;}
{DIGITO}+ {  return NUM;}
{ESPACO} {}
{ENTER} { yylineno++;return ENTER;}
"+" { return MAIS;}
"-" { return MENOS;}
"<" { return MENIGUAL; }
">" { return MAIIGUAL; }
"*" { return VEZES; }
"/" { return DIV; }
"(" { return ABREPAR; }
")" { return FECHAPAR; }
"[" { return ABRECOL; }
"]" { return FECHACOL; }
"{" { return ABRECH; }
"}" { return FECHACH; }
"=" { return IGUAL; }
"==" { return IGUALIGUAL;}
";" { return PVIRG;}
"," { return VIRG;}
.   { ECHO; return ERRO;}

<<EOF>> return FIMARQ;
%%
Token retornaToken(FILE* arq)
{
    yyin = arq;
    yylex();
}

