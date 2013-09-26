#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "grille.h"
#include "jeu.h"

#define PIXEL 50
#define ENTETE 50

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
void affiche_grille (grille g);

//affichage d'un grille avec cairo
void affiche_grille_cairo(grille g,cairo_surface_t * surface);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

//Débute le jeu avec un affichage graphique
void debut_jeu_cairo(grille *g, grille *gc);

#endif
