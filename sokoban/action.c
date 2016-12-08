//BASKEVITCH Claire 21500568
//gestion des actions faites pas le joueur et toutes les fonctions associées aux différentes actions possibles

#include <uvsqgraphics.h>
#include "constantes.h"
#include "action.h"


PLATEAU deplacer_perso(PLATEAU P, int fleche){
				
	if (fleche == FLECHE_HAUT){
		P.la_case[P.perso.x][P.perso.y].mode = VIDE;
		P.perso.y +=1;
		P.la_case[P.perso.x][P.perso.y].mode = PERSO;
		}
	if (fleche == FLECHE_BAS){
		P.la_case[P.perso.x][P.perso.y].mode = VIDE;
		P.perso.y -=1;
		P.la_case[P.perso.x][P.perso.y].mode = PERSO;
		}
	
	if (fleche == FLECHE_GAUCHE){
		P.la_case[P.perso.x][P.perso.y].mode = VIDE;
		P.perso.x -=1;
		P.la_case[P.perso.x][P.perso.y].mode = PERSO;
		}
		
	if (fleche == FLECHE_DROITE){
		P.la_case[P.perso.x][P.perso.y].mode = VIDE;
		P.perso.x +=1;
		P.la_case[P.perso.x][P.perso.y].mode = PERSO;
		}
		
	return P;
	}
	
PLATEAU gestion_touche(PLATEAU P, char touche){
	
	return P;
	}

PLATEAU gestion_clic(PLATEAU P, POINT p){
	
	return P;
	}

//fonction qui récupère l'action du joueur et appelle les fonctions associées à l'action faite
//cette fonction est celle appelée dans le main
PLATEAU fait_action(PLATEAU P){
	int fleche, event;
	char touche;
	POINT p;
	
	event = wait_key_arrow_clic(&touche,&fleche,&p);
	
	if (event == EST_FLECHE) P = deplacer_perso(P,fleche);
	if (event == EST_TOUCHE) gestion_touche(P, touche);
	if (event == EST_CLIC) gestion_clic(P,p);
	
	return P;
	}
