//BASKEVITCH Claire 21500568
//gestion des actions faites pas le joueur et toutes les fonctions associées aux différentes actions possibles

#include "constantes.h"
#include "historique.h"

#ifndef __JOUER_H
#define __JOUER_H

struct info{
	char* nom_fic;
	int niveau;
	int coups_joues;
	int nb_niv;
	};
typedef struct info INFO;

PLATEAU fait_action(PLATEAU P, INFO* I, PILE *pileU, PILE *pileR);


#endif
