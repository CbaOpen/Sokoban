//BASKEVITCH Claire 21500568
//fonction de création de niveau

#include <stdio.h>
#include <stdlib.h>
#include "editeur.h"
#include "constantes.h"
#include "interface.h"

//fait correspondre chaque etat et mode au symbole correspondant 
char choix_symbole(PLATEAU P,int x, int y){
	char c;
	
	if (P.la_case[x][y].mode == MUR) c = '#';
	if (P.la_case[x][y].etat == RANGEMENT) c = '.';
	if (P.la_case[x][y].mode == CAISSE) c = '$';
	if (P.la_case[x][y].mode == PERSO) caractere = '@';
	if ((P.la_case[x][y].etat == RANGEMENT) && (P.la_case[x][y].mode == CAISSE)) c = '*';
	if ((P.la_case[x][y].etat == RANGEMENT) && (P.la_case[x][y].mode == PERSO)) c = '+';
	return c;
	}

//écris dans le fichier de creation de niveau
void ecrire_niveau(PLATEAU P, char *str, int niveau){
	char c;
		
	FILE* fic = fopen(str, "w");
	if (fic==NULL){
		fprintf(stderr,"echec ouverture fichier %s\n",s);
		exit(EXIT_FAILURE);
		}
	
	fprintf(fic,"; ");
	fprintf(fic,"%d\n\n",niveau);
	
	for(y=N-1;y>=0;y--){
		for(x=0;x<N;x++){
			c = choix_symbole(P,x,y);
			fprintf(fic,c);
			}
		fprintf(fic,"\n");
		}
	fclose(fic);
	}

PLATEAU mode_etat(PLATEAU P, POINT a){
	int x,y;
	
	x = a.x/TAILLE_CASE;
	y = a.y/TAILLE_CASE;
	
	P.la_case[x][y].mode = (P.la_case[x][y].mode + 1)%4;
	P.la_case[x][y].état = (P.la_case[x][y].état + 1)%2;
	if (P.la_case[x][y].mode == MUR) .la_case[x][y].état = RIEN;
	
	
	return P;
	}

//verifie qu'il y a bien un seul personnage, nb emplacement de rangement >= nb caisses
int verifier_condition(PLATEAU P){
	
	}
	
PLATEAU action_edit(PLATEAU P){
	POINT a; 
	
	do{
		a = wait_clic();
		P = mode_etat(P,a);
		affiche_sokoban_editeur(P);
		
	}while((p.y<N*TAILLE_CASE) && verifier_condition(P));
	
	
	
	return P;
	}

void creer_niveau(PLATEAU P,char *nom_fichier, int niveau){
	P = recuperer_action_edit(P);
	ecrire_niveau(P,nom_fichier,niveau);
	}
