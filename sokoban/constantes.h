//BASKEVITCH Claire 21500568
//Toutes les constantes utilisées dans le programme

#ifndef __CONSTANTE_H
#define __CONSTANTE_H

//taille du plateau
#define N_LARG 32
#define N_HAUT 20

//structure du plateau
	//structure d'une case
	struct une_case {
		int mode;  //mode personnage ou caisse
		int etat;  //case vide, pleine(mur), emplacemment rangement: non changeable en mode jeu
		};
	
	//structure qui permet de pointer l'emplacement du personnage
	struct coordonnees{
		int x,y;
		};
	
struct plateau {
	struct une_case la_case[N_LARG][N_HAUT];
	struct coordonnees perso;
	};

typedef struct plateau PLATEAU;


//mode d'une case
#define VIDE 0
#define MUR 1
#define CAISSE 2
#define PERSO 3


//etat d'une case
#define RIEN 0
#define RANGEMENT 1

//mode d'action (historique, recommencer niveau, changement de niveau, quitter le jeu)
#define DEFAUT 0
#define UNDO 1
#define REDO 2
#define INIT 3
#define PRECEDENT 4
#define SUIVANT 5
#define QUITTER 6

//mode d'action en plus pour l'editeur
#define PLACER 7
#define BOUGER 8
#define BOUGER_HASARD 9
#define ENREGISTRER 10

//constantes liées à la selection d'une caisse lors de l'édition d'un niveau
#define SELECT_DROITE 1
#define SELECT_GAUCHE -1
#define SELECT_HAUT 2
#define SELECT_BAS -2

//contantes utilisées pendant le test du niveau fermé
#define HAUT 1
#define DROITE 2
#define BAS 3
#define GAUCHE 4

//constantes liées à l'affichage
#define TAILLE_CASE 40
#define LARG_BOUTON ((N_LARG*TAILLE_CASE)/6)
#define HAUT_BOUTON (TAILLE_CASE)
#define LARG_FENETRE (N_LARG*TAILLE_CASE)
#define HAUT_FENETRE (N_HAUT*TAILLE_CASE + 2*HAUT_BOUTON)
#define TAILLE_POLICE 20

//les différentes couleures
#define COUL_CAISSE marron
#define COUL_CAISSE_RANGE darkkhaki
#define COUL_MUR bleumarine
#define COUL_PERSO gold
#define COUL_VIDE lightskyblue

#endif
