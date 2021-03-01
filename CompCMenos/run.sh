#\!/bin/bash
bison -d parse.y
flex scan.l 
gcc -c lex.yy.c
gcc main.c lex.yy.o parse.tab.c definitions.c symtab.c analyze.c cgen.c -o exec -lfl -ly
./exec
