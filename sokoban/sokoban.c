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
#include "jouer.h"

//calcul le nombre total de niveau dans un fichier
int nb_niv_total(char* str){
	int nb=0;
	char c;
	
	FILE* fic = fopen(str,"r");
	if (fic == NULL){
		fprintf(stderr,"echec ouverture fichier %s\n",str);
		exit(EXIT_FAILURE);
		}
	
	do{
		c=fgetc(fic);
		if(c == ';') nb++;
		}while(c != EOF);
	return nb;
	}

//test d'un niveau fini
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
	if (argc != 4 || strcmp(argv[1], "-n")!=0){ //si pas les bons arguments mis
		fprintf(stderr, "erreur dans la ligne de commande\nformat attendu:\n%s -n niveau nomFichier\n",argv[0]);
		exit(EXIT_FAILURE);
		}
	
	PLATEAU P;
	INFO I;
	
	//initialisation du jeu
	init_affichage();
	P = init_plateau(P);
	P = lecture_fichier(P,argv[3],argv[2]);
	
	I.niveau = atof(argv[2]);
	I.nom_fic = argv[3];
	I.coups_joues = 0;
	I.nb_niv = nb_niv_total(I.nom_fic);
	
	//jeu
	while(1){
		affiche_sokoban_jeu(P,&I);
		sleep(1);
		P = fait_action(P, &I);
		
		
		if(niveau_fini(P)){
			I.niveau +=1;
			sprintf(argv[2],"%d",I.niveau);
			P = init_plateau(P);
			P = lecture_fichier(P,I.nom_fic,argv[2]);
			}
		}
	wait_escape();
	exit(0);
	}
