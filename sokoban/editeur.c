//BASKEVITCH Claire 21500568
//fonction de création de niveau

#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include <math.h>
#include "editeur.h"
#include "editeur_action.h"
#include "constantes.h"
#include "lecture_ecriture.h"

//test s'il y a un seul personnage sur le plateau
//cette fonction est testée lorsque le joueur choisi le mode bouger ou bouger au hasard
int test_un_perso(PLATEAU P)
{
	int n = 0, x, y;

	for (x = 0; x < N_LARG; x++) {
		for (y = 0; y < N_HAUT; y++) {
			if (P.la_case[x][y].mode == PERSO)
				n++;
		}
	}
	if (n == 1)
		return TRUE;
	return FALSE;
}

//fonction pour trouver le personnage
PLATEAU trouver_perso(PLATEAU P)
{
	int x, y;

	for (x = 0; x < N_LARG; x++) {
		for (y = 0; y < N_HAUT; y++) {
			if (P.la_case[x][y].mode == PERSO) {
				P.perso.x = x;
				P.perso.y = y;
				return P;
			}
		}
	}
	return P;
}

int test_bord(struct coordonnees coord)
{
	return coord.x == (N_LARG - 1) || coord.x == 0
	    || coord.y == (N_HAUT - 1) || coord.y == 0;
}

//revoie les nouvelles coorddonnées en fonction de la direction
struct coordonnees new_coord(struct coordonnees coord, int direction)
{
	switch (direction) {
	case 1:		//adjacent = HAUT
		coord.y += 1;
		return coord;
	case 2:		//adjacent = DROITE
		coord.x += 1;
		return coord;
	case 3:		//adjacent = BAS
		coord.y += -1;
		return coord;
	default:		//adjacent = GAUCHE
		coord.x += -1;
		return coord;
	}
}

//foncton recursive qui test si une case est un mur ou au bord de la fenetre graphique
//cmp est une variable qui vaut zéro tant que les coordonnées de la case traitée ne vérifie pas te test des bords de la fenetre
//si elle vaut 1, la fonction s'arrete à la fin du dépilement des appels et elle n'effectue pas les tests sur les autres dirrections
int niveau_ferme(PLATEAU P, struct coordonnees coord, int direction1,
		 int direction2)
{
	int cmp = 0;

	if (P.la_case[coord.x][coord.y].mode == MUR)
		return 0;
	if (test_bord(coord) == TRUE)
		return 1;
	if (direction1 == DROITE) {
		if (direction2 == BAS) {	//section droite_bas
			cmp += niveau_ferme(P, new_coord(coord, DROITE), DROITE,
					 BAS);
			if (cmp == 0)
				cmp += niveau_ferme(P, new_coord(coord, BAS), DROITE, BAS);
		} else {	//section droite_haut
			cmp += niveau_ferme(P, new_coord(coord, HAUT), DROITE, HAUT);
			if (cmp == 0)
				cmp += niveau_ferme(P, new_coord(coord, DROITE), DROITE, HAUT);
		}
	} else {
		if (direction2 == BAS) {	//section gauche_bas
			cmp +=
			    niveau_ferme(P, new_coord(coord, GAUCHE), GAUCHE,
					 BAS);
			if (cmp == 0)
				cmp +=
				    niveau_ferme(P, new_coord(coord, BAS),
						 GAUCHE, BAS);
		} else {	//section haut_gauche
			cmp +=
			    niveau_ferme(P, new_coord(coord, HAUT), GAUCHE,
					 HAUT);
			if (cmp == 0)
				cmp +=
				    niveau_ferme(P, new_coord(coord, GAUCHE),
						 GAUCHE, HAUT);
		}
	}
	return cmp;
}

//fonction qui gère les tests pour vérifier si le niveau est fermé
//le plateau de jeu est divisé en 4 sections qui vont être testé les uns à la suite des autres
//cmp vaut 0 tant que la section est fermée
//si le test niveau_fermé renvoi cmp>0 alors les tests suivant ne sont pas effectués
int test_niveau_ferme(PLATEAU P)
{
	int cmp = 0;

	cmp = niveau_ferme(P, P.perso, DROITE, BAS);
	if (cmp == 0)
		cmp = niveau_ferme(P, P.perso, DROITE, HAUT);
	if (cmp == 0)
		cmp = niveau_ferme(P, P.perso, GAUCHE, BAS);
	if (cmp == 0)
		cmp = niveau_ferme(P, P.perso, GAUCHE, HAUT);
	if (cmp != 0)
		return FALSE;
	return TRUE;
}

//appelle les fonctions de test niveau fermé et un seul personnage
//
PLATEAU les_tests(PLATEAU P, char **str, int *mode_action)
{
	if ((*mode_action == BOUGER || *mode_action == BOUGER_HASARD) && test_un_perso(P) == FALSE) {
		*mode_action = PLACER;
		free(*str);
		*str = strdup("Il faut un personnage");
	} else {
		P = trouver_perso(P);
	}
	if ((*mode_action == BOUGER || *mode_action == BOUGER_HASARD)
	    && test_niveau_ferme(P) == FALSE) {
		*mode_action = PLACER;
		free(*str);
		*str = strdup("niveau pas ferme");
	}
	return P;
}

//fonction qui s'occupe de placer les objets
PLATEAU placer_objet(PLATEAU P, POINT a)
{
	int x, y;
	x = a.x / TAILLE_CASE;
	y = a.y / TAILLE_CASE;

	P.la_case[x][y].mode = (P.la_case[x][y].mode + 1) % 4;
	P.la_case[x][y].etat = RIEN;
	if (P.la_case[x][y].mode == CAISSE)
		P.la_case[x][y].etat = RANGEMENT;
	return P;
}

//fonction pour sélectionner une caisse
//vérifie que la case cliquée est bien une caisse et est adjacente au personnage
//2 cas: soit la caisse n'était pas sélectionnée et la sélectionne soit la caisse était sélectionnée et la déselctionne
int select_caisse(PLATEAU P, POINT p, int caisse_select, int *nb_deplacement)
{
	int x, y;
	x = p.x / TAILLE_CASE;
	y = p.y / TAILLE_CASE;

	if (P.la_case[x][y].mode != CAISSE || (fabs(P.perso.x - x) != 1 && fabs(P.perso.y - y) != 1) || (fabs(P.perso.x - x) == fabs(P.perso.y - y)))
		return caisse_select;
	*nb_deplacement = 0;
	if (caisse_select != 0) {
		if (P.perso.x - x == -1 && caisse_select == SELECT_DROITE)
			return 0;
		if (P.perso.x - x == 1 && caisse_select == SELECT_GAUCHE)
			return 0;
		if (P.perso.y - y == 1 && caisse_select == SELECT_BAS)
			return 0;
		if (P.perso.y - y == -1 && caisse_select == SELECT_HAUT)
			return 0;
	} else {
		if (P.perso.x - x == 1)
			return SELECT_GAUCHE;
		if (P.perso.x - x == -1)
			return SELECT_DROITE;
		if (P.perso.y - y == 1)
			return SELECT_BAS;

	}
	return SELECT_HAUT;
}

//change le mode d'action en Placer, bouger, bouger hasars, enregistrer et quitter
PLATEAU changer_mode_action(PLATEAU P, POINT p, int *mode_action, char **str)
{
	if (p.x < 5 * LARG_BOUTON)
		*mode_action = QUITTER;
	if (p.x < 4 * LARG_BOUTON)
		*mode_action = ENREGISTRER;
	if (p.x < 3 * LARG_BOUTON) {
		*mode_action = BOUGER_HASARD;
		P = les_tests(P, str, mode_action);
	}
	if (p.x < 2 * LARG_BOUTON) {
		*mode_action = BOUGER;
		P = les_tests(P, str, mode_action);
	}
	if (p.x < LARG_BOUTON)
		*mode_action = PLACER;
	return P;
}

//associe les clics aux actions correspondantes 
PLATEAU gestion_clic_editeur(PLATEAU P, char **str, POINT p, int *mode_action,
			     int *caisse_select, int *nb_deplacement)
{
	if (p.y >= (HAUT_FENETRE - HAUT_BOUTON))
		P = changer_mode_action(P, p, mode_action, str);
	else {
		if (*mode_action == PLACER)
			P = placer_objet(P, p);
		if (*mode_action == BOUGER)
			*caisse_select =
			    select_caisse(P, p, *caisse_select, nb_deplacement);
	}
	return P;
}

//associe les touches du clavier au mode d'action correspondant
PLATEAU gestion_touche_editeur(PLATEAU P, char touche, int *mode_action,
			       char **str)
{
	if (touche == 'P')
		*mode_action = PLACER;
	if (touche == 'B') {
		*mode_action = BOUGER;
		P = les_tests(P, str, mode_action);
	}
	if (touche == 'H') {
		*mode_action = BOUGER_HASARD;
		P = les_tests(P, str, mode_action);
	}
	if (touche == 'E')
		*mode_action = ENREGISTRER;
	if (touche == 'Q')
		*mode_action = QUITTER;
	return P;
}

//fonction appelé dans le main qui gère les actions faites par le joueur
PLATEAU faire_action_editeur(PLATEAU P, int *mode_action, char **str, int *caisse_select, int *nb_deplacement, char *nom_fichier)
{
	int event = 0, fleche = 0, n;
	char touche;
	POINT p;
	p.x = 0;
	p.y = 0;

	event = wait_key_arrow_clic(&touche, &fleche, &p);

	if (strcmp(*str, "Que l'inspiration soit avec vous") != 0) {
		free(*str);
		*str = strdup("Que l'inspiration soit avec vous");
	}

	if (event == EST_FLECHE && *mode_action == BOUGER) {
		P = deplacer_perso_editeur(P, fleche, *caisse_select,
					   nb_deplacement);
		attendre(300);
	}
	if (event == EST_CLIC)
		P = gestion_clic_editeur(P, str, p, mode_action, caisse_select, nb_deplacement);
	if (event == EST_TOUCHE)
		P = gestion_touche_editeur(P, touche, mode_action, str);
	if (*mode_action == BOUGER_HASARD)
		for (n = 0; n < 10; n++)
			P = deplacer_hasard(P);
	if (*mode_action == ENREGISTRER) {
		ecrire_niveau(P, nom_fichier, nb_niveau(nom_fichier));
		*mode_action = QUITTER;
	}
	if (*mode_action == QUITTER) {
		free(*str);
		exit(EXIT_SUCCESS);
	}

	return P;
}
