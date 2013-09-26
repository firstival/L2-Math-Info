#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

extern int mode_vieillissement;

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
//Ajoute 1 pour faire vieillir la cellule
static inline void vieillir(int i,int j,grille g){g.cellules[i][j]++;}
// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
// Si le mode voisinage cyclique est activé
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] != 0;}

// teste si la cellule (i,j) de la grille g est vivante
// Si le mode voisinage cyclique est désactivé
static inline int est_vivante_non_cyclique(int i, int j, grille g){return (i>=0 && i<g.nbl && 0<=j && j<g.nbc) && (g.cellules[i][j] != 0);}

//typedef de pointeur de fonction, pour des tableaux de fonction fonctionnant par rapport aux variables globales des modes de vieillesse et de voisins cyclique
typedef int (*fct_vivant) (int,int,grille);
typedef int (*fct_vieillesse) (int,int,int,grille);
typedef void (*fct_vivre) (int,int,grille);

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
