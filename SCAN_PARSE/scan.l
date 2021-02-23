%{
#include "definitions.h"
/* lexema do token descoberto */
char lexema[MAX_TAM_TOKEN+1];
char ID_nome[MAX_TAM_TOKEN + 1];
char NUM_val[MAX_TAM_TOKEN + 1];
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
            if (c == '\n') numlinha++;
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
"!=" { return DIF;}
";" { return PVIRG;}
"," { return VIRG;}
{LETRA}({LETRA}|{DIGITO})* { strncpy(ID_nome,yytext,MAX_TAM_TOKEN);return ID;}
{DIGITO}+ { strncpy(NUM_val,yytext,MAX_TAM_TOKEN);return NUM;}
{ESPACO} {}
{ENTER} { numlinha++;}
.   { ECHO; return ERRO;}
<<EOF>> { return YYEOF;}
%%
Token retornaToken(void)
{
    static bool primeira_vez = true;
    Token t;
    if (primeira_vez){
        yyin = arq_cod_fonte; // manda ler do arquivo com o código fonte
        yyout = stdout;
        numlinha++;
        primeira_vez = false;
    }
    t = yylex();
    strncpy(lexema,yytext,MAX_TAM_TOKEN);// guarda conteúdo da string lida
    //printf(" TOKEN: %s\n",nome_token(t));
    //printf(" STRING TOKEN:: %s\n\n",lexema);
    return t;
}

