//BASKEVITCH Claire 21500568
//fonction de création de niveau

#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include "editeur.h"
#include "constantes.h"
#include "interface.h"

//fait correspondre chaque etat et mode au symbole correspondant 
/*char choix_symbole(PLATEAU P,int x, int y){
	char* c;
	
	if (P.la_case[x][y].mode == MUR) c = "#";
	if (P.la_case[x][y].etat == RANGEMENT) c = ".";
	if (P.la_case[x][y].mode == CAISSE) c = "$";
	if (P.la_case[x][y].mode == PERSO) c = "@";
	if ((P.la_case[x][y].etat == RANGEMENT) && (P.la_case[x][y].mode == CAISSE)) c = "*";
	if ((P.la_case[x][y].etat == RANGEMENT) && (P.la_case[x][y].mode == PERSO)) c = "+";
	return c;
	}

//écris dans le fichier de creation de niveau
void ecrire_niveau(PLATEAU P, char *nom_fichier, int niveau){
	char* c;
	int x,y;
		
	FILE* fic = fopen(nom_fichier, "w");
	if (fic==NULL){
		fprintf(stderr,"echec ouverture fichier %s\n",nom_fichier);
		exit(EXIT_FAILURE);
		}
	
	fprintf(fic,"; ");
	fprintf(fic,"%d\n\n",niveau);
	
	for(y=N-1;y>=0;y--){
		for(x=0;x<N;x++){
			c = choix_symbole(P,x,y);
			fprintf(fic,"%s",c);
			}
		fprintf(fic,"\n");
		}
	fprintf(fic,"\n");
	fclose(fic);
	}*/

void changer_mode_action(POINT p, int* mode_action){
	if (p.x < 5*LARG_BOUTON) *mode_action = QUITTER;
	if (p.x < 4*LARG_BOUTON) *mode_action = ENREGISTRER;
	if (p.x < 3*LARG_BOUTON) *mode_action = BOUGER_HASARD;
	if (p.x < 2*LARG_BOUTON) *mode_action = BOUGER;
	if (p.x < LARG_BOUTON)   *mode_action = PLACER;
	}

PLATEAU placer_objet(PLATEAU P, POINT a){
	int x,y;
	x = a.x/TAILLE_CASE;
	y = a.y/TAILLE_CASE;
	
	P.la_case[x][y].mode = (P.la_case[x][y].mode + 1)%4;
	P.la_case[x][y].etat = RIEN;
	if (P.la_case[x][y].mode == CAISSE) P.la_case[x][y].etat = RANGEMENT;
	return P;
	}

PLATEAU deplacer_perso_editeur(PLATEAU P){
	
	return P;
	}

PLATEAU deplacer_hasard(PLATEAU P){
	
	return P;
	}

PLATEAU select_caisse(PLATEAU P, POINT p){
	
	return P;
	}

//test s'il y a un seul personnage sur le plateau
//cette fonction est testée lorsque le joueur choisi le mode bouger ou bouger au hasard
int test_un_perso(PLATEAU P){
	int n=0,x,y;
	
	for(x=0;x<N;x++){
		for(y=0;y<N;y++) { if(P.la_case[x][y].mode == PERSO) n++; }
		}
	if(n == 1) return TRUE;
	return FALSE;
	}

//associe les clics aux actions correspondantes	
PLATEAU gestion_clic_editeur(PLATEAU P,POINT p,int *mode_action){
	if (p.y>= (HAUT_FENETRE - HAUT_BOUTON)) changer_mode_action(p, mode_action);
	else{
		if (*mode_action == PLACER) P = placer_objet(P,p);
		if (*mode_action == BOUGER) P = select_caisse(P,p);
		} 
	return P;
	}

//associe les touches du clavier au mode d'action correspondant
void gestion_touche_editeur(char touche, int *mode_action){
	if (touche == 'P') *mode_action = PLACER;
	if (touche == 'B') *mode_action = BOUGER;
	if (touche == 'H') *mode_action = BOUGER_HASARD;
	if (touche == 'E') *mode_action = ENREGISTRER;
	if (touche == 'Q') *mode_action = QUITTER;
	}

//fonction appelé dans le main qui gère les actions faites par le joueur
PLATEAU faire_action_editeur(PLATEAU P, int *mode_action, char **str){
	int event=0, fleche=0;
	char touche;
	POINT p; p.x=0; p.y=0;
	
	event = wait_key_arrow_clic(&touche, &fleche, &p);
	
	if(event == EST_FLECHE) P = deplacer_perso_editeur(P);
	if(event == EST_CLIC) P = gestion_clic_editeur(P,p, mode_action);
	if (event == EST_TOUCHE) gestion_touche_editeur(touche, mode_action);
	
	if((*mode_action == BOUGER || *mode_action == BOUGER_HASARD) && test_un_perso(P)!=1){
		*mode_action = PLACER;
		free(*str);
		*str = strdup("Il faut un personnage");
		}
	else if(strcmp(*str,"Que l'inspiration soit avec vous") !=0) {
		free(*str);
		*str = strdup("Que l'inspiration soit avec vous");
		}
		
	if (*mode_action == BOUGER_HASARD) P = deplacer_hasard(P);
	if(*mode_action == ENREGISTRER) ;
	if(*mode_action == QUITTER) { free(*str); exit(0); }
			
	return P;
	}

