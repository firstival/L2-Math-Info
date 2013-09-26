#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

//fonction qui compte le nombre de voisin de manière cyclique de la cellule (i,j)
int compte_voisins_vivants_cyclique (int i, int j, grille g);

//fonction qui compte le nombre de voisin de manière non-cyclique de la cellule (i,j)
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

//fonction qui teste si une cellule doit doit mourrir ou vieillir : utilisée uniquement en mode vieillissement
int test_vieillesse(int v,int x,int y,grille g);
//fonction qui teste si une cellule doit mourrir : utilisée uniquement en mode immortelle
int test_immortelle(int v,int x,int y,grille g);

#endif
