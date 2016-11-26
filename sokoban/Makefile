#BASKEVITCH Claire 21500568

CFLAGS=-c -g -Wall

all:sokoban
	./sokoban
	
test: clean compil
	./sokoban -n 8 sasquatch1.xsb

compil: sokoban
	

sokoban: sokoban.o interface.o
	gcc -o sokoban sokoban.o interface.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf


sokoban.o: sokoban.c constantes.h 
	gcc $(CFLAGS) `sdl-config --cflags` sokoban.c

interface.o: interface.c interface.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` interface.c

clean:
	rm -f sokoban
	rm -f sokoban.o
	rm -f interface.o
