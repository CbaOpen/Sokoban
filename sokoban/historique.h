//BASKEVITCH Claire 21500568
//gestion de l'historique qui fonctionera avec une pile

#include "contantes.h"

#ifndef __HISTORIQUE_H
#define __HISTORIQUE_H

//structure des éléments de l'historique 

struct historique{
	int caisse; //vaut 0 si aucune caisse déplacé dans le déplacement suivant vaut 1 si une caisse est déplacé
	int direction; //direction de déplacement pour la caisse (contantes de uvsq graphics), vaut 0 si aucune caisse deplacée
	struct personnage perso; //coordonnées du personnage
	};
	
typedef historique HISTORIQUE;

struct element{
	HISTORIQUE histo;
	struct element* suiv;
	};

typedef struct element Element;

struct Pile{
	Element *premier;
	};

typedef struct Pile PILE;

PILE creer_pile();

void empiler(PILE *pile, struct personnage p, int caisse_dep, int direction);

HISTORIQUE depiler(PILE *pile);

#endif
