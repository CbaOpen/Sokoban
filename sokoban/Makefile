#BASKEVITCH Claire 21500568

CFLAGS=-c -g -Wall

all: compil
	./sokoban -n 1 sasquatch1.xsb
	
test: clean compil
	./sokoban -n 8 sasquatch1.xsb

compil: sokoban
	

sokoban: sokoban.o interface.o action.o
	gcc -o sokoban sokoban.o interface.o action.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

sokoban.o: sokoban.c constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` sokoban.c

interface.o: interface.c interface.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` interface.c

action.o: action.c action.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` action.c

clean:
	rm -f sokoban
	rm -f sokoban.o
	rm -f interface.o
