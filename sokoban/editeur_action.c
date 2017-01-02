//BASKEVITCH Claire 21500568
//fonctions des déplacements utilisé dans l'éditeur

#include <stdlib.h>
#include <time.h>
#include <uvsqgraphics.h>
#include "constantes.h"
#include "editeur_action.h"


//test si la case adjacente à laquelle on veut aller est un mur ou une caisse
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
	

//fonction de déplacement lorsqu'aucune caisse n'a pas été sélectionnée 
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
	

//fonction de déplacement lorsqu'une caisse a été selectionnée
PLATEAU deplacer_select(PLATEAU P, int fleche, int caisse_select, int *nb_deplacement){
		//cas 1: la caisse à droite a été sélectionnée
	if (caisse_select == SELECT_DROITE){
		if (fleche == FLECHE_HAUT || fleche == FLECHE_BAS) return P; //empeche le personnage d'aller en haut et en bas
		if(fleche == FLECHE_DROITE) {
			if (*nb_deplacement == 0) return P; //test si le joueur peut revenir en arrière
			P = deplacer(P,1,0);
			P.la_case[P.perso.x+1][P.perso.y].mode = CAISSE;
			*nb_deplacement += -1;
			return P;
			}
		if (test2(P,-1,0) == TRUE){
			P = deplacer(P,-1,0);
			P.la_case[P.perso.x+1][P.perso.y].mode = CAISSE;
			P.la_case[P.perso.x+2][P.perso.y].mode = VIDE;
			*nb_deplacement += 1;
			}
		return P;
		}
		//cas 2: la caisse à gauche a été sélectionnée
	if (caisse_select == SELECT_GAUCHE){
		if (fleche == FLECHE_HAUT || fleche == FLECHE_BAS) return P;
		if(fleche == FLECHE_GAUCHE) {
			if (*nb_deplacement == 0) return P;
			P = deplacer(P,-1,0);
			P.la_case[P.perso.x-1][P.perso.y].mode = CAISSE;
			*nb_deplacement += -1;
			return P;
			}
		if(test2(P,1,0) == TRUE){
			P = deplacer(P,1,0);
			P.la_case[P.perso.x-1][P.perso.y].mode = CAISSE;
			P.la_case[P.perso.x-2][P.perso.y].mode = VIDE;
			*nb_deplacement += 1;
			}
		return P;
		}
		//cas 3: la caisse en haut a été sélectionnée
	if (caisse_select == SELECT_HAUT){
		if (fleche == FLECHE_GAUCHE || fleche == FLECHE_DROITE) return P;
		if(fleche == FLECHE_HAUT) {
			if (*nb_deplacement == 0) return P;
			P = deplacer(P,0,1);
			P.la_case[P.perso.x][P.perso.y+1].mode = CAISSE;
			*nb_deplacement += -1;
			return P;
			}
		if (test2(P,0,-1) == TRUE){
			P = deplacer(P,0,-1);
			P.la_case[P.perso.x][P.perso.y+1].mode = CAISSE;
			P.la_case[P.perso.x][P.perso.y+2].mode = VIDE;
			*nb_deplacement += 1;
			}
		return P;
		}
		//cas 4: la caisse en bas a été sélectionnée
	if (fleche == FLECHE_GAUCHE || fleche == FLECHE_DROITE) return P;
		if(fleche == FLECHE_BAS) {
			if (*nb_deplacement == 0) return P;
			P = deplacer(P,0,-1);
			P.la_case[P.perso.x][P.perso.y-1].mode = CAISSE;
			*nb_deplacement += -1;
			return P;
			}
		if (test2(P,0,1) == TRUE){
			P = deplacer(P,0,1);
			P.la_case[P.perso.x][P.perso.y-1].mode = CAISSE;
			P.la_case[P.perso.x][P.perso.y-2].mode = VIDE;
			*nb_deplacement += 1;
			}
	return P;
	}

//fonction qui gère les déplacements 
PLATEAU deplacer_perso_editeur(PLATEAU P, int fleche, int caisse_select, int *nb_deplacement){
	if (caisse_select == 0){
		P = deplacer_normal(P,fleche);
		}
	else {
		P = deplacer_select(P,fleche,caisse_select, nb_deplacement);
		}
	return P;
	}

//
int alea_fleche(PLATEAU P, int caisse_select){
	int fleche = alea_int(50)%4;
	
	if(caisse_select == 0){
		if(fleche == 0 && test2(P,0,1)){ fleche = FLECHE_HAUT; return fleche; }
		else fleche++; 
		if(fleche == 1 && test2(P,1,0)) { fleche = FLECHE_DROITE; return fleche; }
		else fleche++;
		if(fleche == 2 && test2(P,0,-1)){ fleche = FLECHE_BAS;	return fleche; }
		fleche = FLECHE_GAUCHE;
		return fleche;
			}
	if (caisse_select == SELECT_DROITE || caisse_select == SELECT_GAUCHE){
		if (fleche == 0 || fleche == 2) { fleche = FLECHE_DROIT; return fleche; }
		else { fleche = FLECHE_GAUCHE; return fleche; }
		}
	if (fleche == 0 || fleche == 2) { fleche = FLECHE_HAUT; return fleche; }
	fleche = FLECHE_BAS; return fleche;
	}

//
int test_caisse_adj(PLATEAU P){
	int nb=0;
	
	if (P.la_case[P.perso.x][P.perso.y+1].mode == CAISSE) nb++;
	if (P.la_case[P.perso.x][P.perso.y-1].mode == CAISSE) nb++;
	if (P.la_case[P.perso.x+1][P.perso.y].mode == CAISSE) nb++;
	if (P.la_case[P.perso.x-1][P.perso.y].mode == CAISSE) nb++;
	return nb;
	}

//
int rechercher_caisse(PLATEAU P, int place){
	int cmp=0;
	
	switch(place){
		case 1:
			if(P.la_case[P.perso.x][P.perso.y+1].mode == CAISSE) return SELECT_HAUT;
			if(P.la_case[P.perso.x+1][P.perso.y].mode == CAISSE) return SELECT_DROITE;
			if(P.la_case[P.perso.x][P.perso.y-1].mode == CAISSE) return SELECT_BAS;
			return SELECT_GAUCHE;
		case 2:
			if(P.la_case[P.perso.x][P.perso.y+1].mode == CAISSE) cmp++;
			if(P.la_case[P.perso.x+1][P.perso.y].mode == CAISSE && cmp == 1) return SELECT_DROITE;
			else cmp++;
			if(P.la_case[P.perso.x][P.perso.y-1].mode == CAISSE && cmp == 1) return SELECT_BAS;
			return SELECT_GAUCHE;
		case 3:
			if(P.la_case[P.perso.x][P.perso.y+1].mode == CAISSE) cmp++;
			if(P.la_case[P.perso.x+1][P.perso.y].mode == CAISSE && cmp == 2) return SELECT_DROITE;
			else cmp++;
			if(P.la_case[P.perso.x][P.perso.y-1].mode == CAISSE && cmp == 2) return SELECT_BAS;
			return SELECT_GAUCHE;
		default:
			return SELECT_GAUCHE;
		}
	}

//
int alea_select(PLATEAU P, int nb_caisse){
	srand(time(NULL));
	
	if (nb_caisse == 1) return rechercher_caisse(P,1);
	if (nb_caisse == 2) return rechercher_caisse(P,alea_int(2)+1);
	if (nb_caisse == 3) return rechercher_caisse(P, alea_int(3)+1);
	return rechercher_caisse(P, alea_int(4)+1);
	}

//
PLATEAU deplacer_hasard(PLATEAU P){
	int caisse_select = 0, nb_deplacement = 0;
	int N, alea, fleche, nb_caisse;
	
	for (N = 0; N < 300; N++){
		if (caisse_select != 0){
			alea = alea_int(10);
			if (alea != 0){
				fleche = alea_fleche(P, caisse_select);
				P = deplacer_select(P, fleche, caisse_select, &nb_deplacement);
				}
			else { caisse_select = 0; nb_deplacement =0; }
			}
		else {
			nb_caisse = test_caisse_adj(P);
			if (nb_caisse > 0){
				alea = alea_int(50)%2;
				if (alea == 0){
					fleche = alea_fleche(P,caisse_select);
					P = deplacer_normal(P, fleche);
					}
				else {
					caisse_select = alea_select(P, nb_caisse);
					}
				}
			else { 
				fleche = alea_fleche(P,caisse_select);
				P = deplacer_normal(P, fleche);
				}
			}
		}
	return P;
	}
