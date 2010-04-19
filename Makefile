all: main.o wiimote_funcs.o
	clang -lm -lwiiuse -g main.o wiimote_funcs.o -o wiiuse-basic

main.o: main.c
	clang -std=c99 -lm -lwiiuse -Wall -g -c main.c -o main.o

wiimote_funcs.o: wiimote_funks.c
	clang -std=99 -lm -lwiiuse -Wall -g -c wiimote_func.c -o wiimote_funccs.o


clean:
	rm *.o
	rm wiiuse-basic
