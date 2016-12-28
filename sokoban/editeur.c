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
	if (P.la_case[x][y].mode == PERSO) { P.perso.x = x; P.perso.y = y; }
	return P;
	}

////test si la case adjacente à laquelle on veut aller est un mur ou une caisse
int test2(PLATEAU P,int x, int y){ //x et y sont des variables qui correspondent au déplacement du perso (x pour les déplacement gauche-droite, y pour haut-bas)
	if (P.la_case[P.perso.x+x][P.perso.y+y].mode == MUR) return FALSE;
	if (P.la_case[P.perso.x+x][P.perso.y+y].mode == CAISSE) return FALSE;
	if (P.perso.x+x<0 || P.perso.x+x>N_LARG-1 || P.perso.y+y<0 || P.perso.y+y>N_HAUT-1) return FALSE;
	return TRUE;
	}

PLATEAU deplacer(PLATEAU P, int x, int y){
	P.la_case[P.perso.x][P.perso.y].mode = VIDE; 
	P.la_case[P.perso.x+x][P.perso.y+y].mode = PERSO;
	P.perso.x += x;
	P.perso.y += y;
	return P;
	}

PLATEAU deplacer_normal(PLATEAU P, int fleche){
	if (fleche == FLECHE_HAUT){
			if (test2(P,0,1) == TRUE) P = deplacer(P,0,1);
			return P;
			}
		if (fleche == FLECHE_BAS){
			if (test2(P,0,-1) == TRUE) P = deplacer(P,0,-1);
			return P;
			}
		if (fleche == FLECHE_GAUCHE){
			if (test2(P,-1,0) == TRUE) P = deplacer(P,-1,0);
			return P;
			}
		if (fleche == FLECHE_DROITE){
			if (test2(P,1,0) == TRUE) P = deplacer(P,1,0);
			}
		return P;
	}

PLATEAU deplacer_perso_editeur(PLATEAU P, int fleche, int caisse_select){
	//int result;
	
	if (caisse_select == 0){
		P = deplacer_normal(P,fleche);
		}
	else {
		
		}
	return P;
	}

PLATEAU deplacer_hasard(PLATEAU P){
	//a finir
	return P;
	}

int select_caisse(PLATEAU P, POINT p, int caisse_select){
	if (caisse_select != 0){
		// a finir
		}
	else {
		
		}
	
	return caisse_select;
	}

//test s'il y a un seul personnage sur le plateau
//cette fonction est testée lorsque le joueur choisi le mode bouger ou bouger au hasard
int test_un_perso(PLATEAU P){
	int n=0,x,y;
	
	for(x=0;x<N_LARG;x++){
		for(y=0;y<N_HAUT;y++) { if(P.la_case[x][y].mode == PERSO) n++; }
		}
	if(n == 1) return TRUE;
	return FALSE;
	}

//associe les clics aux actions correspondantes	
PLATEAU gestion_clic_editeur(PLATEAU P,POINT p,int *mode_action, int *caisse_select){
	if (p.y>= (HAUT_FENETRE - HAUT_BOUTON)) changer_mode_action(p, mode_action);
	else{
		if (*mode_action == PLACER) P = placer_objet(P,p);
		if (*mode_action == BOUGER) *caisse_select = select_caisse(P,p,*caisse_select);
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
	int event=0, fleche=0, caisse_select=0;
	char touche;
	POINT p; p.x=0; p.y=0;
	
	event = wait_key_arrow_clic(&touche, &fleche, &p);
	
	if(event == EST_FLECHE && *mode_action == BOUGER) P = deplacer_perso_editeur(P,fleche,caisse_select);
	if(event == EST_CLIC) P = gestion_clic_editeur(P,p, mode_action, &caisse_select);
	if (event == EST_TOUCHE) gestion_touche_editeur(touche, mode_action);
	
	if((*mode_action == BOUGER || *mode_action == BOUGER_HASARD) && test_un_perso(P)!= TRUE){
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

