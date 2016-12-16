//BASKEVITCH Claire 21500568
//gestion des actions faites pas le joueur et toutes les fonctions associées aux différentes actions possibles

#include <uvsqgraphics.h>
#include "constantes.h"
#include "action.h"
#include "lecture.h"

//test si la case adjacente à laquelle on veut aller est un mur ou une caisse
//si c'est une caisse, test si la case adjacente à la caisse est un mur ou une caisse
//vaut 0 si le personnage ne peut pas se déplacer
//vaut 1 si rien n'est sur son chemin
//vaut 2 s'il y a une caisse qui peut être déplacée
int test(PLATEAU P,int x, int y){ //x et y sont des variables qui correspondent au déplacement du perso (x pour les déplacement gauche-droite, y pour haut-bas)
	if (P.la_case[P.perso.x+x][P.perso.y+y].mode == MUR) return 0;
	if (P.la_case[P.perso.x+x][P.perso.y+y].mode == CAISSE){
		if (P.la_case[P.perso.x+x*2][P.perso.y+y*2].mode == VIDE) return 2;
		return 0;
		}
	return 1; 
	}

//déplace le personnage et renvoie le nouveau plateau
PLATEAU deplacer_perso(PLATEAU P, int fleche, int *coups_joues){
	int result;
			
	if (fleche == FLECHE_HAUT){
		result = test(P,0,1);
		
		if (result == 0) return P;
		if (result == 1){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.y +=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			*coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.y +=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x][P.perso.y+1].mode = CAISSE;
			*coups_joues += 1;
			return P;
			}
		}
		
	if (fleche == FLECHE_BAS){
		result = test(P,0,-1);
		
		if (result == 0) return P;
		if (result == 1){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.y -=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			*coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.y -=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x][P.perso.y-1].mode = CAISSE;
			*coups_joues += 1;
			return P;
			}
		}
	
	if (fleche == FLECHE_GAUCHE){
		result = test(P,-1,0);
		
		if (result == 0) return P;
		if (result == 1){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.x -=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			*coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.x -=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x-1][P.perso.y].mode = CAISSE;
			*coups_joues += 1;
			return P;
			}
		}
		
	if (fleche == FLECHE_DROITE){
		result = test(P,1,0);
		
		if (result == 0) return P;
		if (result == 1){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.x +=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			*coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.x +=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x+1][P.perso.y].mode = CAISSE;
			*coups_joues += 1;
			return P;
			}
		}
	return P;
	}
	
int gestion_touche(char touche, int *niveau){
	
	return DEFAUT;
	}

int gestion_clic(POINT p, int *niveau){
	if (p.y<(HAUT_FENETRE-HAUT_BOUTON)) return DEFAUT;
	if (p.x<LARG_BOUTON) return UNDO;
	if (p.x < (LARG_BOUTON*2)) return REDO;
	if (p.x < (LARG_BOUTON*3)) return INIT;
	if ((p.x < (LARG_BOUTON*4) && p.x > (LARG_BOUTON*3)) && (*niveau>1)){
		*niveau = *niveau - 1;
		return PRECEDENT;
		}
	if ((p.x < (LARG_BOUTON*5) && p.x > (LARG_BOUTON*4)) && (*niveau<50)){
		*niveau = *niveau + 1;
		return SUIVANT;
		}
	if (p.x < LARG_FENETRE && p.x > (LARG_BOUTON*5)) {
		return QUITTER;
		}
	return DEFAUT;
	}

PLATEAU gestion_action_bouton(PLATEAU P, int bouton, int *niveau, char* str){
	char str_niv[10];
	sprintf(str_niv,"%d",*niveau);
	printf("%s\n",str_niv);
	
	if (bouton == QUITTER) exit(0);
	if (bouton == UNDO){
		//fct undo
		return P;
		}
	if (bouton == REDO){
		//fct redo
		return P;
		}
	if (bouton == INIT || bouton == PRECEDENT || bouton == SUIVANT){
		P = init_plateau(P);
		P = lecture_fichier(P, str, str_niv);
		return P;
		}
	return P;
	}

//fonction qui récupère l'action du joueur et appelle les fonctions associées à l'action faite
//cette fonction est celle appelée dans le main
PLATEAU fait_action(PLATEAU P, int *niveau, int *coups_joues, char* str){
	int fleche=0, event=0;
	char touche;
	POINT p;
	int bouton=DEFAUT;
	
	event = wait_key_arrow_clic(&touche,&fleche,&p);
	
	if (event == EST_FLECHE) {
		P = deplacer_perso(P,fleche, coups_joues);
		return P;
		}
	if (event == EST_TOUCHE) bouton = gestion_touche(touche, niveau);
	if (event == EST_CLIC) bouton = gestion_clic(p, niveau);
	P = gestion_action_bouton(P, bouton, niveau, str);
	return P;
	}
