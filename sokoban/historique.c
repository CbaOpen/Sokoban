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

void empiler(PILE *pile, struct coordonnees p, int caisse_dep, int direction, int test){
	Element *nouveau = malloc(sizeof(Element));
	if (pile == NULL || nouveau == NULL) {
		printf("probleme d'allocation memoire ou le pointeur pile pointe vers NULL au lieu d'une struct pile");
		exit(EXIT_FAILURE);
		}
	
	nouveau->histo.test=test;
	nouveau->histo.perso = p;
	nouveau->histo.caisse = caisse_dep;
	nouveau->histo.direction = direction;
	nouveau->suiv = pile->premier;
	pile->premier = nouveau;
	
	} 

//retourne une variable de type historique
//libère la mémoire de l'élément enlevé
HISTORIQUE depiler(PILE *pile){
	
	if (pile == NULL) {
		printf("le pointeur pile pointe vers NULL au lieu d'une struct pile");
		exit(EXIT_FAILURE);
		}
	
	HISTORIQUE H;
	Element *elt_depile = pile->premier;
	
	H.test = elt_depile->histo.test;
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
	Element *tmp;
	
	while(pile->premier != NULL){
		tmp = pile->premier;
		pile->premier = tmp->suiv;
		free(tmp);
		
		}
	}

//fonction de déplacement à l'endroit (utilisé dans fct_redo et undo_init)
PLATEAU a_lendroit(HISTORIQUE H, PLATEAU P){
	P.la_case[P.perso.x][P.perso.y].mode = VIDE;
	P.perso.x = H.perso.x;
	P.perso.y = H.perso.y;
		
	if(H.caisse != 0){
		if (H.direction == FLECHE_HAUT)	P.la_case[P.perso.x][P.perso.y+1].mode = CAISSE;
		if(H.direction == FLECHE_BAS) P.la_case[P.perso.x][P.perso.y-1].mode = CAISSE;
		if(H.direction == FLECHE_GAUCHE) P.la_case[P.perso.x-1][P.perso.y].mode = CAISSE;
		if(H.direction == FLECHE_DROIT) P.la_case[P.perso.x+1][P.perso.y].mode = CAISSE;
		}
		
	P.la_case[P.perso.x][P.perso.y].mode = PERSO;
	return P;
	}

//fonction de déplacement à l'envers (utilisé dans fct_undo et redo_init)
//si le déplacement indique un deplacement vers le haut, alors le perso se déplace d'une case vers le bas, idem pour les autres déplacements
//s'il y a eu une caisse de déplacé, alors la case du perso prend le mode caisse et le perso recule
PLATEAU a_lenvers(HISTORIQUE H, PLATEAU P){
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

//dépile tout jusqu'à que la valeur test soit différente de 1
//joue depuis le point de départ du niveau jusqu'au point atteint lors du dernier déplacement enregistré avant l'initialisation du niveau
PLATEAU undo_init(PILE *pileU, PILE *pileR, PLATEAU P){
	HISTORIQUE H;
	
	while((pileU->premier != NULL) && (pileU->premier->histo.test == 1)){
		H = depiler(pileU);
		empiler(pileR,H.perso,H.caisse,H.direction,H.test);
		P = a_lendroit(H,P);
		}
	return P;
	}

//revient à l'initialisation du niveau
PLATEAU redo_init(PILE *pileU, PILE *pileR, PLATEAU P){
	HISTORIQUE H;
	
	while((pileR->premier != NULL) && (pileR->premier->histo.test == 1)){
		H = depiler(pileR);
		empiler(pileU,H.perso,H.caisse,H.direction,H.test);
		P = a_lenvers(H,P);
		}
	return P;
	}

//fonction undo
//si le test indique qu'il y a eu une initialisation (test == 1), appel de la fonction qui gère le dépilement d'une initialisation 
//sinon depile la pile undo et empile ce qui a été dépilé dans la pile redo et appelle la fonction a_lenvers
PLATEAU fct_undo(PILE *pileU,PILE *pileR, PLATEAU P){
		if(pileU->premier->histo.test == 1) {
			P = undo_init(pileU, pileR, P);
			}
		else{
			HISTORIQUE H;
			H = depiler(pileU);
			empiler(pileR,H.perso,H.caisse,H.direction,H.test);
			P = a_lenvers(H,P);			
			}
		return P;
	}

//fonction redo
//depile la pile redo et empile ce qui a été dépilé dans la pile undo
PLATEAU fct_redo(PILE *pileU,PILE *pileR, PLATEAU P){
	if(pileR->premier->histo.test == 1) {
		P = redo_init(pileU, pileR, P);
		}
	else{
		HISTORIQUE H;
		H = depiler(pileR);
		empiler(pileU,H.perso,H.caisse,H.direction,H.test);
		P = a_lendroit(H,P);
		}
		return P;
	}

//dépile toutes les actions enregistrées dans la pile undo et recopie dans une pile p1 (les actions se retrouvent dans le sens inverse)
//réempile dans la pile undo et dans une pile p2
//la valeur des tests dans p2 sont égaux à 1
//empile toutes les actions de p2 dans undo (les actions sont dans le sens inverse)
void empiler_historique_init(PILE *pileU){
	PILE p1, p2;
	HISTORIQUE H;
	
	p1 = creer_pile();
	p2 = creer_pile();
	
	while(pileU->premier != NULL){
		H = depiler(pileU);
		empiler(&p1,H.perso,H.caisse,H.direction,H.test);
		}
	while(p1.premier != NULL){
		H = depiler(&p1);
		empiler(pileU,H.perso,H.caisse,H.direction,H.test);
		empiler(&p2,H.perso,H.caisse,H.direction,1);
		}
	
	while(p2.premier != NULL){
		H = depiler(&p2);
		empiler(pileU,H.perso,H.caisse,H.direction,H.test);
		}
		free(p1.premier);
		free(p2.premier);
		
	}
