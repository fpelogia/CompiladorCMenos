#\!/bin/bash
flex scan.l 
gcc main.c lex.yy.c definitions.c -o exec -lfl
./exec 
rm exec
