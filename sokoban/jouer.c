//BASKEVITCH Claire 21500568
//gestion des actions faites pas le joueur et toutes les fonctions associées aux différentes actions possibles

#include <uvsqgraphics.h>
#include "constantes.h"
#include "jouer.h"
#include "lecture.h"
#include "historique.h"

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
//gère cas par cas les déplacements vers le haut, le bas, la droite et la gauche
//rajoute le nouveau déplacement à l'historique
PLATEAU deplacer_perso(PLATEAU P, int fleche, INFO* I,PILE *pileU,PILE *pileR){
	int result;
	initialisation(pileR); //car si on s'est déplacé dans l'historique, lorsque l'on fait un nouveau déplacement, la pile redo doit se vider
			
	if (fleche == FLECHE_HAUT){
		result = test(P,0,1);
		
		if (result == 0) return P;
		if (result == 1){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.y +=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			empiler(pileU,P.perso,0,FLECHE_HAUT);
			I->coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.y +=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x][P.perso.y+1].mode = CAISSE;
			empiler(pileU,P.perso,1,FLECHE_HAUT);
			I->coups_joues += 1;
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
			empiler(pileU,P.perso,0,FLECHE_BAS);
			I->coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.y -=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x][P.perso.y-1].mode = CAISSE;
			empiler(pileU,P.perso,1,FLECHE_BAS);
			I->coups_joues += 1;
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
			empiler(pileU,P.perso,0,FLECHE_GAUCHE);
			I->coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.x -=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x-1][P.perso.y].mode = CAISSE;
			empiler(pileU,P.perso,1,FLECHE_GAUCHE);
			I->coups_joues += 1;
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
			empiler(pileU,P.perso,0,FLECHE_DROIT);
			I->coups_joues += 1;
			return P;
			}
		if (result == 2){
			P.la_case[P.perso.x][P.perso.y].mode = VIDE;
			P.perso.x +=1;
			P.la_case[P.perso.x][P.perso.y].mode = PERSO;
			P.la_case[P.perso.x+1][P.perso.y].mode = CAISSE;
			empiler(pileU,P.perso,1,FLECHE_DROITE);
			I->coups_joues += 1;
			return P;
			}
		}
	return P;
	}

//renvoi le mode d'action demandé par les touches du clavier
int gestion_touche(char touche, INFO* I){
	if (touche == 'U') return UNDO;
	if (touche == 'R') return REDO;
	if (touche == 'I') return INIT;
	if ((touche == 'P') && (I->niveau>1)){
		I->niveau = I->niveau - 1;
		return PRECEDENT;
		}
	if ((touche == 'S') && (I->niveau < I->nb_niv)){
		I->niveau = I->niveau + 1;
		return SUIVANT;
		}
	if (touche == 'Q') return QUITTER;
	return DEFAUT;
	}

//renvoi le mode d'action demandé par la souris
int gestion_clic(POINT p, INFO* I){
	if (p.y<(HAUT_FENETRE-HAUT_BOUTON)) return DEFAUT;
	if (p.x<LARG_BOUTON) return UNDO;
	if (p.x < (LARG_BOUTON*2)) return REDO;
	if (p.x < (LARG_BOUTON*3)) return INIT;
	if (p.x < (LARG_BOUTON*4)){
		if(I->niveau>1){
			I->niveau = I->niveau - 1;
			return PRECEDENT;
			}
		else return DEFAUT;
		}
	if (p.x < (LARG_BOUTON*5)){
		if (I->niveau < I->nb_niv){
			I->niveau = I->niveau + 1;
			return SUIVANT;
			}
		else return DEFAUT;
		}
	if (p.x < LARG_FENETRE) {
		return QUITTER;
		}
	return DEFAUT;
	}

//execute les fonctions des boutons
PLATEAU gestion_action_bouton(PLATEAU P, int bouton, INFO* I, PILE *pileU, PILE *pileR){
	char str_niv[10];
			
	if (bouton == QUITTER) {
		initialisation(pileU);
		initialisation(pileR);
		exit(0);
		}
		
	if ((bouton == UNDO) && (pileU->premier != NULL)){
		P = fct_undo(pileU,pileR, P);
		return P;
		}
		
	if (bouton == REDO && (pileR->premier != NULL)){
		P = fct_redo(pileU,pileR, P);	
		return P;
		}
		
	if (bouton == INIT){
		sprintf(str_niv,"%d",I->niveau);
		printf("%s\n",str_niv); //bug étrange qui n'apparait pas quand il y a le printf (explication du bug dans le rapport)
		P = init_plateau(P);
		P = lecture_fichier(P, I->nom_fic, str_niv);
		return P;
		}
		
	if (bouton == PRECEDENT || bouton == SUIVANT){
		initialisation(pileU);
		initialisation(pileR);
		sprintf(str_niv,"%d",I->niveau);
		P = init_plateau(P);
		P = lecture_fichier(P, I->nom_fic, str_niv);
		I->coups_joues = 0;
		}
	return P;
	}

//fonction qui récupère l'action du joueur et appelle les fonctions associées à l'action faite
//cette fonction est celle appelée dans le main
PLATEAU fait_action(PLATEAU P, INFO* I, PILE *pileU, PILE *pileR){
	int fleche=0, event=0;
	char touche;
	POINT p; p.x=0; p.y=0;
	int bouton=DEFAUT;
	
	event = wait_key_arrow_clic(&touche,&fleche,&p);
	
	if (event == EST_FLECHE) {
		P = deplacer_perso(P,fleche, I, pileU, pileR);
		return P;
		}
	if (event == EST_TOUCHE) bouton = gestion_touche(touche, I);
	if (event == EST_CLIC) bouton = gestion_clic(p, I);
	P = gestion_action_bouton(P, bouton, I, pileU, pileR);
	return P;
	}
