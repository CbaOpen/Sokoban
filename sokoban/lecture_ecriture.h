//BASKEVITCH Claire 21500568
//lecture et écriture d'un fichier

#include "constantes.h"

PLATEAU init_plateau(PLATEAU P);

PLATEAU lecture_fichier(PLATEAU P, char *str, char *niveau);

void ecrire_niveau(PLATEAU P, char *nom_fichier, int niveau);

int nb_niveau(char *nom_fichier);
