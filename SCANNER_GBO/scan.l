%{
#include "definitions.h"
%}
DIGITO [0-9]
LETRA [a-zA-Z]
ESPACO [ \t]+
ENTER \n
%%
"/*"             { char c;
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
"else" { /*printf("\t");puts(yytext);*/return ELSE;}
"if" { /*printf("\t");puts(yytext);*/ return IF;}
"int" { /*printf("\t");puts(yytext);*/return INT;}
"return" { /*printf("\t");puts(yytext);*/return RETURN;}
"void" { /*printf("\t");puts(yytext);*/return VOID;}
"while" { /*printf("\t");puts(yytext);*/return WHILE;}
{LETRA}({LETRA}|{DIGITO})* {/* printf("\t%d: ID, val= %s\n", numlinha, yytext); */return ID;}
{DIGITO}+ { /*printf("\'t%d: NUM, val=%s\n", numlinha, yytext);*/ return NUM;}
{ESPACO} {/*ignora espaço*/}
{ENTER} { /*numlinha++;ECHO;*/yylineno++;return ENTER;}
"+" { /*printf("\t%d: +\n",numlinha);*/return MAIS;}
"-" {/* printf("\t%d: -\n",numlinha);*/return MENOS;}
"<" {/* printf("\t%d: <\n",numlinha);*/return MENIGUAL; }
">" {/* printf("\t%d: >\n",numlinha);*/return MAIIGUAL; }
"*" {/* printf("\t%d: *\n",numlinha);*/return VEZES; }
"/" {/* printf("\t%d: /\n",numlinha);*/return DIV; }
"(" {/* printf("\t%d: (\n",numlinha);*/return ABREPAR; }
")" {/* printf("\t%d: )\n",numlinha);*/return FECHAPAR; }
"[" {/* printf("\t%d: [\n",numlinha);*/return ABRECOL; }
"]" {/* printf("\t%d: ]\n",numlinha);*/return FECHACOL; }
"{" {/* printf("\t%d: {\n",numlinha);*/return ABRECH; }
"}" {/* printf("\t%d: }\n",numlinha);*/return FECHACH; }
"=" {/* printf("\t%d: =\n",numlinha);*/return IGUAL; }
"==" {/* printf("\t%d: ==\n",numlinha);*/ return IGUALIGUAL;}
";" {/* printf("\t%d: ;\n", numlinha);*/ return PVIRG;}
"," {/* printf("\t%d: ;\n", numlinha);*/ return VIRG;}
.               {/* puts(yytext);*/ECHO;return ERRO;}

<<EOF>> return FIMARQ;
%%
Token retornaToken(FILE* arq)
{
    /*
    if (argc == 2)
    {
        if(f_in = fopen(argv[1],"r")) yyin = f_in;
        else perror(argv[0]);
    }
    else yyin = stdin;
    */
    yyin = arq;
    yylex();
}

