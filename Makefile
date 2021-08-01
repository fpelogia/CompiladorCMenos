all:
	bison -d src/parse.y
	mv *.c src/
	mv *.h src/
	flex src/scan.l 
	mv *.c src/
	gcc -c src/lex.yy.c
	mv *.o src/
	gcc src/main.c src/lex.yy.o src/parse.tab.c src/definitions.c src/symtab.c src/analyze.c src/cgen.c -o CompCMenos -lfl -ly
clean:
	rm CompCMenos
	rm src/*.tab.c
	rm src/*.tab.h
	rm src/*.yy.c
	rm src/*.o
