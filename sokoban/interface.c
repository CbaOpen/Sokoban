//BASKEVITCH Claire 21500568
//fonction d'affichage du plateau en mode jeu et création

#include <uvsqgraphics.h>
#include "interface.h"
#include "constantes.h"
#include "jouer.h"

//initialise la fenetre graphique ainsi que le mode d'affichage (ici mode automatique off)
void init_affichage(){
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	SDL_WM_SetCaption("BASKEVITCH Claire - Projet Sokoban (2016)",NULL);
	affiche_auto_off();
	}
	
//fonction qui affiche une caisse
void affiche_caisse(int x, int y,int etat){
	POINT bg,hd;
	
	bg.x = x*TAILLE_CASE; bg.y = y*TAILLE_CASE;
	hd.x = bg.x + TAILLE_CASE; hd.y = bg.y + TAILLE_CASE;
	if (etat == RANGEMENT) draw_fill_rectangle(bg,hd,COUL_CAISSE_RANGE);
	else draw_fill_rectangle(bg,hd,COUL_CAISSE);
	}

//fonction qui affiche le personnage
void affiche_perso(int x, int y){
	POINT centre;
	
	centre.x = x*TAILLE_CASE + TAILLE_CASE/2;
	centre.y = y*TAILLE_CASE + TAILLE_CASE/2;
	draw_fill_circle(centre,15,COUL_PERSO);
	}

//fonction qui affiche un mur
void affiche_mur(int x, int y){
	POINT bg,hd;
	
	bg.x = x*TAILLE_CASE; bg.y = y*TAILLE_CASE;
	hd.x = bg.x + TAILLE_CASE; hd.y = bg.y + TAILLE_CASE;
	draw_fill_rectangle(bg,hd,COUL_MUR);
	}

//fonction qui affiche un emplacement de rangement
void affiche_rangement(int x,int y){
	POINT bas,haut;
	
	bas.x = x*TAILLE_CASE; bas.y = y*TAILLE_CASE;
	haut.x = (x+1)*TAILLE_CASE; haut.y = (y+1)*TAILLE_CASE;
	draw_line(bas,haut,white);
	
	bas.x = haut.x;
	haut.x = x*TAILLE_CASE;
	draw_line(bas,haut,white);
	}

//affiche le plateau de jeu
void affiche_plateau(PLATEAU P){
	int x,y;
	
	for (x=0; x<N_LARG; x++){
		for (y=0 ; y<N_HAUT ; y++){
			if (P.la_case[x][y].mode == MUR) affiche_mur(x,y);
			if (P.la_case[x][y].etat == RANGEMENT) affiche_rangement(x,y);
			if (P.la_case[x][y].mode == CAISSE) affiche_caisse(x,y,P.la_case[x][y].etat);
			if (P.la_case[x][y].mode == PERSO) affiche_perso(x,y);
			}
		}	
	}

//fonction qui affiche un des boutons redo,undo, etc. 
//la_selection vaut ou 1 selon le mode qu'on utilise dans l'éditeur
//utile seulement dans la partie éditeur, vaut toujours 0 dans la partie jouer
void affiche_un_bouton(int x, char *texte, int la_selection){
	POINT bg,hd,centre;
	COULEUR coul_texte = la_selection*noir + (1 - la_selection)*rouge;
	
	bg.x = x*LARG_BOUTON; bg.y = HAUT_FENETRE - HAUT_BOUTON;
	hd.x = bg.x + LARG_BOUTON; hd.y = HAUT_FENETRE;
	centre.x = bg.x + LARG_BOUTON/2; centre.y = HAUT_FENETRE - HAUT_BOUTON/2;
	
	draw_rectangle(bg,hd,noir);
	aff_pol_centre(texte,TAILLE_POLICE,centre,coul_texte);
	}

//affiche les informations sur nom du fichier, niveau, et nombre de coups joués
void affiche_info_jeu(char *nom_fichier,char *niveau, int coups_joues){
	POINT bg,hd,centre;
	
	bg.x = 0; bg.y = HAUT_FENETRE - 2*HAUT_BOUTON;
	hd.x = LARG_FENETRE; hd.y = HAUT_FENETRE - HAUT_BOUTON;
	centre.x =3*N_LARG; centre.y = hd.y - HAUT_BOUTON/2;
	
	draw_fill_rectangle(bg,hd,antiquewhite);
	draw_rectangle(bg,hd,noir);
	
	aff_pol_centre("fichier:",TAILLE_POLICE,centre,noir);
	centre.x =centre.x + 5*N_LARG;
	aff_pol_centre(nom_fichier,TAILLE_POLICE,centre,noir);
	
	centre.x = centre.x + LARGEUR_FENETRE/4;
	aff_pol_centre("niveau:",TAILLE_POLICE,centre,noir);
	centre.x =centre.x + 3*N_LARG;
	aff_pol_centre(niveau,TAILLE_POLICE,centre,noir);
	
	centre.x = centre.x + LARGEUR_FENETRE/4;
	aff_pol_centre("coups joues:",TAILLE_POLICE,centre,noir);
	centre.x =centre.x + 3*N_LARG; centre.y = centre.y + HAUT_BOUTON/3;
	aff_int(coups_joues,TAILLE_POLICE,centre,noir);
	} 

//afficher les 6 boutons de l'interface de jeu
void affiche_les_boutons_jeu(){
	POINT bg,hd;
	
	bg.x = 0; bg.y = HAUT_FENETRE - HAUT_BOUTON;
	hd.x = LARG_FENETRE; hd.y = HAUT_FENETRE;
	draw_fill_rectangle(bg,hd,antiquewhite);
	
	affiche_un_bouton(0,"UNDO",0);
	affiche_un_bouton(1,"REDO",0);
	affiche_un_bouton(2,"INITIALISER",0);
	affiche_un_bouton(3,"PRECEDENT",0);
	affiche_un_bouton(4,"SUIVANT",0);
	affiche_un_bouton(5,"QUITTER",0);
	}

void affiche_info_editeur(char* str){
	POINT centre,hd,bg;
	
	bg.x = 0; bg.y = HAUT_FENETRE - 2*HAUT_BOUTON;
	hd.x = LARG_FENETRE; hd.y = HAUT_FENETRE - HAUT_BOUTON;
	centre.x = LARG_FENETRE/2;
	centre.y = HAUT_FENETRE-(3*HAUT_BOUTON/2);
	
	draw_fill_rectangle(bg,hd,antiquewhite);
	draw_rectangle(bg,hd,noir);
	aff_pol_centre(str,TAILLE_POLICE,centre,noir);
	}
	
//affiche le bouton enregistrer du mode editeur de niveau
void affiche_les_boutons_editeur(int mode_action){
	POINT bg,hd;
	
	bg.x = 0; bg.y = HAUT_FENETRE - HAUT_BOUTON;
	hd.x = LARG_FENETRE; hd.y = HAUT_FENETRE;
	draw_fill_rectangle(bg,hd,antiquewhite);
	
	affiche_un_bouton(0,"PLACER",mode_action==PLACER);
	affiche_un_bouton(1,"BOUGER",mode_action==BOUGER);
	affiche_un_bouton(2,"BOUGER HASARD",mode_action==BOUGER_HASARD);
	affiche_un_bouton(3,"ENREGISTRER",mode_action==ENREGISTRER);
	affiche_un_bouton(4,"QUITTER",mode_action==QUITTER);
	
	}
	
//affiche le plateau de jeu quand on joue
void affiche_sokoban_jeu(PLATEAU P,INFO* I){
	char niv[10];
	
	sprintf(niv,"%d",I->niveau);
	fill_screen(COUL_VIDE);
	affiche_plateau(P);
	affiche_les_boutons_jeu();
	affiche_info_jeu(I->nom_fic,niv,I->coups_joues);
	affiche_all();
	}

//affiche le plateau de jeu quand on est en mode edition
void affiche_sokoban_editeur(PLATEAU P, char* str, int mode_action){
	fill_screen(COUL_VIDE);
	affiche_plateau(P);
	affiche_les_boutons_editeur(mode_action);
	affiche_info_editeur(str);
	affiche_all();
	}
