//BASKEVITCH Claire 21500568
//gestion de l'historique qui fonctionnera avec une pile

#include <uvsqgraphics.h>
#include "constantes.h"
#include "historique.h"

PILE creer_pile(){
	PILE pile;
	pile.premier = NULL;
	return pile;
	}

void empiler(PILE *pile, struct personnage p, int caisse_dep, int direction){
	Element *nouveau = malloc(sizeof(Element));
	if (pile == NULL || nouveau == NULL) {
		printf("probleme d'allocation memoire ou le pointeur pile pointe vers NULL au lieu d'une struct pile");
		exit(EXIT_FAILURE);
		}
	
	nouveau->histo.perso = p;
	nouveau->histo.caisse = caisse_dep;
	nouveau->histo.direction = direction;
	nouveau->suiv = pile->premier;
	pile->premier = nouveau;
	
	} 

//avant d'appeler fonction, faire test de pile->suiv == NULL
HISTORIQUE depiler(PILE *pile){
	
	if (pile == NULL) {
		printf("le pointeur pile pointe vers NULL au lieu d'une struct pile");
		exit(EXIT_FAILURE);
		}
	
	HISTORIQUE H;
	Element *elt_depile = pile->premier;
	
	H.perso = elt_depile->histo.perso;
	H.caisse = elt_depile->histo.caisse;
	H.direction = elt_depile->histo.direction;
	pile->premier = elt_depile->suiv;
	free(elt_depile);
		
	return H;
	}

void initialisation (PILE *pile){
	if (pile == NULL) {
		printf("le pointeur pile pointe vers NULL au lieu d'une struct pile");
		exit(EXIT_FAILURE);
		}
	
	while(pile->premier != NULL){
		depiler(pile);
		}
	}
	
//fonction undo
//depile la pile undo et empile ce qui a été dépilé dans la pile redo
//si le déplacement indique un deplacement vers le haut, alors le perso se déplace d'une case vers le bas, idem pour les autres déplacements
//s'il y a eu une caisse de déplacé, alors la case du perso prend le mode caisse et le perso recule
PLATEAU fct_undo(PILE *pileU,PILE *pileR, PLATEAU P){
	HISTORIQUE H;
		H = depiler(pileU);
		empiler(pileR,H.perso,H.caisse,H.direction);
		
		P.la_case[P.perso.x][P.perso.y].mode = VIDE;
		if(H.direction == FLECHE_HAUT){
			if (H.caisse != 0){
				P.la_case[P.perso.x][P.perso.y].mode = CAISSE;
				P.la_case[P.perso.x][P.perso.y+1].mode = VIDE;
				}
			P.perso.y = H.perso.y-1;
			}
		if(H.direction == FLECHE_BAS){
			if (H.caisse != 0){
				P.la_case[P.perso.x][P.perso.y].mode = CAISSE;
				P.la_case[P.perso.x][P.perso.y-1].mode = VIDE;
				}
			P.perso.y = H.perso.y+1;
			}
		if(H.direction == FLECHE_GAUCHE){
			if (H.caisse != 0){
				P.la_case[P.perso.x][P.perso.y].mode = CAISSE;
				P.la_case[P.perso.x-1][P.perso.y].mode = VIDE;
				}
			P.perso.x = H.perso.x+1;
			}
		
		if(H.direction == FLECHE_DROIT){
			if (H.caisse != 0){
				P.la_case[P.perso.x][P.perso.y].mode = CAISSE;
				P.la_case[P.perso.x+1][P.perso.y].mode = VIDE;
				}
			P.perso.x = H.perso.x-1;
			}
		P.la_case[P.perso.x][P.perso.y].mode = PERSO;
		return P;
	}
