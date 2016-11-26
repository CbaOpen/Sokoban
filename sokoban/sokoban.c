//BASKEVITCH Claire 21500568
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uvsqgraphics.h>
#include "constantes.h"
#include "interface.h"

//initialise le plateau à vide au lancement du programme
PLATEAU init_plateau(PLATEAU P){
	int x,y;
	
	for(x=0;x<N;x++){
		for (y=0;y<N;y++){
			P.la_case[x][y].mode = VIDE;
			P.la_case[x][y].etat = RIEN;
			}
		}
	return P;
	}
	
//lors de la lecture du fichier, fait correspondre chaque symbole avec sa signification dans le jeu
PLATEAU choix_mode_etat(PLATEAU P, int x, int y, char caractere){
	if (caractere == '#') P.la_case[x][y].mode = MUR;
	if (caractere == '.') P.la_case[x][y].etat = RANGEMENT;
	if (caractere == '$') P.la_case[x][y].mode = CAISSE;
	if (caractere == '@') P.la_case[x][y].mode = PERSO;
	if (caractere == '*') {
		P.la_case[x][y].etat = RANGEMENT;
		P.la_case[x][y].mode = CAISSE;
		}
	if (caractere == '+') {
		P.la_case[x][y].etat = RANGEMENT;
		P.la_case[x][y].mode = PERSO;
		}
	return P;
	}

//lis le fichier contenant les niveaux et initialise le plateau du jeu
PLATEAU lecture_fichier(PLATEAU P,char *str,char niveau[]){
	int x=0,y=N; //commence lecture en haut à gauche du plateau
	char c[N];
	int caractere=0;
	
	FILE* fic = fopen(str,"r");
	if (fic == NULL){ //test si le fichier est NULL
		fprintf(stderr,"echec ouverture fichier %s\n",str);
		exit(EXIT_FAILURE);
		}
	
	while(strcmp(c,niveau) != 0){ //tant que le curseur n'est pas arrivé au niveau entré en argument
		fscanf(fic,"%s",&c);  //utilisation de strcmp pour comparer des chaines de caractères
		} 
		
	do{ //tant que le curseur n'est pas arrivé à la fin du fichier ou d'un ";"
		caractere = fgetc(fic);
		P = choix_mode_etat(P,x,y,caractere);		
		x++;
		if (caractere == '\n' || !(x<N)) { //si retour à la ligne ou x dépasse N (valeur max du tableau)
			y--;						//passe à la ligne en dessous et remet x à gauche
			x=0;
			}
		}while(caractere != ';' && caractere !=EOF);
	fclose(fic);
	return P;
	}

/////// DEBUT DU MAIN /////////
int main(int argc, char** argv){
	PLATEAU P;
	init_affichage();
	P = init_plateau(P);
	
	if (argc != 4 || strcmp(argv[1], "-n")!=0){ //si pas les bons arguments mis
		fprintf(stderr, "erreur dans la ligne de commande\nformat attendu:\n%s -n nomFichier\n",argv[0]);
		exit(EXIT_FAILURE);
		}
	
	P = lecture_fichier(P,argv[3],argv[2]);
	affiche_sokoban_jeu(P,argv[3],argv[2],50);
		
	wait_escape();
	exit(0);
	}