#BASKEVITCH Claire 21500568

CFLAGS=-c -g -Wall

jouer: compil
	./sokoban -n 1 sasquatch1.xsb
	
test: clean compil
	./sokoban -n 8 sasquatch1.xsb

editeur: compil
	./sokoban -c niveau.xsb

compil: sokoban
	

indent:
	indent -linux sokoban.c historique.c historique.h jouer.c jouer.h lecture_ecriture.c lecture_ecriture.h
	indent -linux interface.c interface.h editeur.c editeur.h editeur_action.c editeur_action.h

sokoban: sokoban.o lecture_ecriture.o interface.o historique.o jouer.o editeur_action.o editeur.o
	gcc -o sokoban sokoban.o lecture_ecriture.o interface.o historique.o jouer.o editeur_action.o editeur.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

sokoban.o: sokoban.c constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` sokoban.c

lecture_ecriture.o: lecture_ecriture.c lecture_ecriture.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` lecture_ecriture.c

interface.o: interface.c interface.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` interface.c

historique.o: historique.c historique.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` historique.c

jouer.o: jouer.c jouer.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` jouer.c

editeur_action.o: editeur_action.c editeur_action.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` editeur_action.c

editeur.o: editeur.c editeur.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` editeur.c

clean:
	rm -f sokoban
	rm -f *.o
