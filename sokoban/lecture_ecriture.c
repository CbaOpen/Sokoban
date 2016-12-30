//BASKEVITCH Claire 21500568
//lecture du fichier

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uvsqgraphics.h>
#include "constantes.h"

//initialise le plateau à vide au lancement du programme
PLATEAU init_plateau(PLATEAU P){
	int x,y;
	
	for(x=0;x<N_LARG;x++){
		for (y=0;y<N_HAUT;y++){
			P.la_case[x][y].mode = VIDE;
			P.la_case[x][y].etat = RIEN;
			}
		}
	P.perso.x = 0;
	P.perso.y = 0;
	return P;
	}

//lors de la lecture du fichier, fait correspondre chaque symbole avec sa signification dans le jeu
PLATEAU choix_mode_etat(PLATEAU P, int x, int y, char caractere){
	if (caractere == '#') P.la_case[x][y].mode = MUR;
	if (caractere == '.') P.la_case[x][y].etat = RANGEMENT;
	if (caractere == '$') P.la_case[x][y].mode = CAISSE;
	if (caractere == '@'){
		P.la_case[x][y].mode = PERSO;
		P.perso.x = x;
		P.perso.y = y;
		}
	if (caractere == '*') {
		P.la_case[x][y].etat = RANGEMENT;
		P.la_case[x][y].mode = CAISSE;
		}
	if (caractere == '+') {
		P.la_case[x][y].etat = RANGEMENT;
		P.la_case[x][y].mode = PERSO;
		P.perso.x = x;
		P.perso.y = y;
		}
	return P;
	}


//lis le fichier contenant les niveaux et initialise le plateau du jeu
PLATEAU lecture_fichier(PLATEAU P,char *str,char* niveau){
	int x=0,y=N_HAUT; //commence lecture en haut à gauche du plateau
	char c[N_LARG];
	int caractere=0;
	
	FILE* fic = fopen(str,"r");
	if (fic == NULL){ //test si le fichier est NULL
		fprintf(stderr,"echec ouverture fichier %s\n",str);
		exit(EXIT_FAILURE);
		}
	
	do{ //tant que le curseur n'est pas arrivé au niveau entré en argument
		fscanf(fic,"%s",&c); 
		}while(strcmp(c,niveau) != 0); 
		
	caractere = fgetc(fic);
	while((caractere != ';') && (caractere !=EOF) && (y>=0)){ //tant que le curseur n'est pas arrivé à la fin du fichier ou d'un ";"
		caractere = fgetc(fic);
		P = choix_mode_etat(P,x,y,caractere);		
		x++;
		if (caractere == '\n' || !(x<N_LARG)) { //si retour à la ligne ou x dépasse N (valeur max du tableau)
			y--;						//passe à la ligne en dessous et remet x à gauche
			x=0;
			}
		}
	fclose(fic);
	return P;
	}


//calcul le nombre de niveau total et renvoie ce nombre+1
int nb_niveau(char *nom_fichier){
	FILE* fic = fopen(nom_fichier, "r");
	if (fic==NULL) return 1;
	
	int c,n=1;
	
	do{
		c = fgetc(fic);
		if (c == ';') n++;
		}while(c != EOF);
		return n;
	}

//fait correspondre chaque etat et mode au symbole correspondant 
int choix_symbole(PLATEAU P,int x, int y){
	int c = ' ';
	
	if (P.la_case[x][y].mode == MUR) c = '#';
	if (P.la_case[x][y].etat == RANGEMENT) c = '.';
	if (P.la_case[x][y].mode == CAISSE) c = '$';
	if (P.la_case[x][y].mode == PERSO) c = '@';
	if ((P.la_case[x][y].etat == RANGEMENT) && (P.la_case[x][y].mode == CAISSE)) c = '*';
	if ((P.la_case[x][y].etat == RANGEMENT) && (P.la_case[x][y].mode == PERSO)) c = '+';
	return c;
	}

int chercher_point_gauche(PLATEAU P){
	int x,y;
	
	for(x=0;x<N_LARG;x++){
		for(y=0;y<N_HAUT;y++) { if(P.la_case[x][y].mode == MUR) return x; }
		}
	return 0;
	}

int chercher_point_droit(PLATEAU P){
	int x,y;
	
	for(x=N_LARG-1;x>0;x--){
		for(y=0;y<N_HAUT;y++) { if(P.la_case[x][y].mode == MUR) return x+1; }
		}
	return N_LARG;
	}


int chercher_point_haut(PLATEAU P){
	int x,y;
	
	for(y=N_HAUT-1;y>=0;y--){
		for(x=0;x<N_LARG;x++) { if(P.la_case[x][y].mode == MUR) return y; }
		}
	return N_HAUT;
	}

int chercher_point_bas(PLATEAU P){
	int x,y;
	
	for(y=0;y<N_HAUT;y++){
		for(x=0;x<N_LARG;x++) { if(P.la_case[x][y].mode == MUR) return y; }
		}
	return 0;
	}
	
//écris dans le fichier de creation de niveau
void ecrire_niveau(PLATEAU P, char *nom_fichier, int niveau){
	int c;
	int x,y, deb_x, deb_y, fin_x, fin_y;
		
	FILE* fic = fopen(nom_fichier, "a");
	if (fic==NULL){
		fprintf(stderr,"echec ouverture fichier %s\n",nom_fichier);
		exit(EXIT_FAILURE);
		}
	
	fprintf(fic,"; ");
	fprintf(fic,"%d\n\n",niveau);
	
	deb_x = chercher_point_gauche(P);
	deb_y = chercher_point_haut(P);
	fin_x = chercher_point_droit(P);
	fin_y = chercher_point_bas(P);
	
	for(y=deb_y;y>=fin_y;y--){
		for(x=deb_x;x<fin_x;x++){
			c = choix_symbole(P,x,y);
			fputc(c,fic);
			}
		fprintf(fic,"\n");
		}
	fprintf(fic,"\n");
	fclose(fic);
	}
