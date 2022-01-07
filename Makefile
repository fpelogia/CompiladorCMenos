all:
	bison -d src/parse.y
	mv *tab.c src/
	mv *tab.h src/
	flex src/scan.l 
	mv *yy.c src/
	gcc -c src/lex.yy.c
	mv *.o src/
	# gcc -g -Og -std=gnu99 src/main.c src/lex.yy.o src/parse.tab.c src/definitions.c src/symtab.c src/analyze.c src/cgen.c -o CompCMenos -lfl -ly
	gcc -g -Og -std=gnu99 src/main.c src/lex.yy.o src/parse.tab.c src/definitions.c src/symtab.c src/analyze.c src/cgen.c -o CompCMenos -lfl 
	cp CompCMenos src/
clean:
	rm CompCMenos
	rm src/CompCMenos
	rm src/*.tab.c
	rm src/*.tab.h
	rm src/*.yy.c
	rm src/*.o
check:
	valgrind --leak-check=full ./CompCMenos
