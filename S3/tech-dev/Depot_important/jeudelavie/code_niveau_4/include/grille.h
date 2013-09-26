#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/***********************
 * TYPES
 ***********************/
// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;

/***********************
 * GESTION DE LA GRILLE
 ***********************/
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);
// libère une grille
void libere_grille (grille* g);
// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);
// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

/***********************
 * GESTION DES CELLULES
 ***********************/

/*** TESTS ***/
// teste si la cellule (i,j) de la grille g est vivante
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] > 0;} 
// teste si la cellule (i,j) de la grille g est viable
static inline int est_viable(int i, int j, grille g){return g.cellules[i][j] >= 0;} 

/*** MODIFICATEURS ***/
// rend vivante la cellule (i,j) de la grille g
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
// rend non-viable la cellule (i,j) de la grille g
static inline void set_nonviable(int i, int j, grille g){g.cellules[i][j] = -1;} 
// la cellule continue à vivre : sans viellissement
void set_ne_viellit_pas(int i, int j, grille g); 
// la cellule continue à vivre : avec viellissement
void set_viellit(int i, int j, grille g); 


#endif
