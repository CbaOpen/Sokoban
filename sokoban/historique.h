//BASKEVITCH Claire 21500568
//gestion de l'historique qui fonctionera avec une pile

#include "constantes.h"

#ifndef __HISTORIQUE_H
#define __HISTORIQUE_H

//structure des éléments de l'historique 

struct historique{
	int caisse; //vaut 0 si aucune caisse déplacé dans le déplacement suivant vaut 1 si une caisse est déplacé
	int direction; //direction de déplacement (contantes de uvsq graphics)
	struct personnage perso; //coordonnées du personnage
	};
	
typedef struct historique HISTORIQUE;

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

void initialisation (PILE *pile);

PLATEAU fct_undo(PILE *pileU,PILE *pileR, PLATEAU P);

#endif
