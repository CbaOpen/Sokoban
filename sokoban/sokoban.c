//BASKEVITCH Claire 21500568
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uvsqgraphics.h>
#include "constantes.h"
#include "lecture.h"
#include "interface.h"
#include "action.h"


	
int niveau_fini(PLATEAU P){
	int x,y;
	
	for(x = 0; x <N; x++){
		for(y = 0; y<N;y++){
			if ((P.la_case[x][y].etat == RANGEMENT) && (P.la_case[x][y].mode != CAISSE)) return 0;
			}
		}
	return 1;
	}


/////// DEBUT DU MAIN /////////
int main(int argc, char** argv){
	int niveau, coups_joues=0;
	PLATEAU P;
	init_affichage();
	P = init_plateau(P);
	
	if (argc != 4 || strcmp(argv[1], "-n")!=0){ //si pas les bons arguments mis
		fprintf(stderr, "erreur dans la ligne de commande\nformat attendu:\n%s -n niveau nomFichier\n",argv[0]);
		exit(EXIT_FAILURE);
		}
	
	P = lecture_fichier(P,argv[3],argv[2]);
	affiche_sokoban_jeu(P,argv[3],argv[2],coups_joues);
	niveau = atof(argv[2]);
	
	while(1){
		P = fait_action(P, &niveau, &coups_joues, argv[3]);
		sprintf(argv[2],"%d",niveau);
		affiche_sokoban_jeu(P,argv[3],argv[2],coups_joues);
		sleep(1);
		if(niveau_fini(P)){
			niveau++;
			sprintf(argv[2],"%d",niveau);
			P = init_plateau(P);
			P = lecture_fichier(P,argv[3],argv[2]);
			affiche_sokoban_jeu(P,argv[3],argv[2],coups_joues);
			}
		}
	wait_escape();
	exit(0);
	}
