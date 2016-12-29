//BASKEVITCH Claire 21500568
//fonction de création de niveau

#include "constantes.h"

#ifndef __EDITEUR_H
#define __EDITEUR_H
/*
typedef struct test_mur{
	struct personnage coord;
	int adjacent;
	}Test_mur;

typedef struct elt{
	Test_mur mur;
	struct elt *suiv;
	} ELT;

typedef struct pile2{ ELT *premier; } PILE2;*/

PLATEAU faire_action_editeur(PLATEAU P, int *mode_action, char **str, int *caisse_select, int *nb_deplacement, char *nom_fichier);

#endif
