//BASKEVITCH Claire 21500568
//gestion de l'historique qui fonctionnera avec une pile

#include <uvsqgraphics.h>
#include "contantes.h"
#include "historique.h"

PILE creer_pile(){
	PILE pile;
	pile.premier = NULL;
	return pile;
	}

void empiler(PILE *pile, struct personnage p, int caisse_dep, int direction){
	Element *nouveau = malloc(sizeof(Element));
	if (pile == NULL || nouveau == NULL) {
		printf("probleme d'allocation memoire ou le pointeur H pointe vers NULL au lieu d'une struct historique");
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
	
	if (H == NULL) {
		printf("le pointeur H pointe vers NULL au lieu d'une struct historique");
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
