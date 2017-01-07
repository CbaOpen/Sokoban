//BASKEVITCH Claire 21500568
//fonction main

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uvsqgraphics.h>
#include "constantes.h"
#include "lecture_ecriture.h"
#include "interface.h"
#include "historique.h"
#include "jouer.h"
#include "editeur.h"

//test d'un niveau fini
int niveau_fini(PLATEAU P)
{
	int x, y;

	for (x = 0; x < N_LARG; x++) {
		for (y = 0; y < N_HAUT; y++) {
			if ((P.la_case[x][y].etat == RANGEMENT)
			    && (P.la_case[x][y].mode != CAISSE))
				return 0;
		}
	}
	return 1;
}

/////// DEBUT DU MAIN /////////
int main(int argc, char **argv)
{
	if (argc != 2 && argc != 3 && argc != 4) {
		fprintf(stderr,
			"erreur dans la ligne de commande\nformat attendu:\n%s -n niveau nomFichier\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}
	
			//mode editeur
	if (strcmp(argv[1], "-c") == 0) {	

		PLATEAU P;
		char *str = strdup("Que l'inspiration soit avec vous");
		int mode_action = PLACER, caisse_select = 0, nb_deplacement = 0;	//caisse_select dit si une caisse a été selectionnée ou non et nb_deplacement compte le nombre de déplacement effectué dans une direction quand une caisse a été sélectionnée
		//utile pour revenir en arrière sans avoir besoin d'un historique
		init_affichage();
		P = init_plateau(P);

		while (1) {
			affiche_sokoban_editeur(P, str, mode_action);
			P = faire_action_editeur(P, &mode_action, &str,
						 &caisse_select,
						 &nb_deplacement, argv[2]);
		}
	}
			//mode jeu//
	PLATEAU P;
	INFO I;
	PILE pileU, pileR;

	//initialisation du jeu
	pileU = creer_pile();
	pileR = creer_pile();

	init_affichage();
	P = init_plateau(P);
	

	if (argc == 2) {
		 P = lecture_fichier(P, argv[1], "1"); 
		 I.niveau = 1; 
		 I.nom_fic = argv[1];
		 }
	else if (strcmp(argv[1],"-n") != 0) printf("erreur sur la ligne de commande\n format attendu: %s [-n ou -c ou rien] [si -n, numéro du niveau] [nom du fichier]\n", argv[0]);
	else { 
		P = lecture_fichier(P, argv[3], argv[2]); 
		I.niveau = atof(argv[2]); 
		I.nom_fic = argv[3];
		}
	
	I.coups_joues = 0;
	I.nb_niv = nb_niveau(I.nom_fic) - 1;

	//jeu
	while (1) {
		affiche_sokoban_jeu(P, &I);
		attendre(300);
		P = fait_action(P, &I, &pileU, &pileR);

		if (niveau_fini(P)) {
			if (I.niveau == I.nb_niv) {
				initialisation(&pileU);
				initialisation(&pileR);
				free(pileU.premier);
				free(pileR.premier);
				exit(EXIT_SUCCESS);
			}
			I.niveau += 1;
			sprintf(argv[2], "%d", I.niveau);
			initialisation(&pileU);
			initialisation(&pileR);
			P = init_plateau(P);
			P = lecture_fichier(P, I.nom_fic, argv[2]);
		}
	}
}

