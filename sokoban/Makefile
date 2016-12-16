#BASKEVITCH Claire 21500568

CFLAGS=-c -g -Wall

jouer: compil
	./sokoban -n 1 sasquatch1.xsb
	
test: compil
	./sokoban -n 30 sasquatch1.xsb

compil: sokoban
	

sokoban: sokoban.o lecture.o interface.o action.o
	gcc -o sokoban sokoban.o lecture.o interface.o action.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

sokoban.o: sokoban.c constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` sokoban.c

lecture.o: lecture.c constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` lecture.c

interface.o: interface.c interface.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` interface.c

action.o: action.c action.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` action.c

clean:
	rm -f sokoban
	rm -f *.o
