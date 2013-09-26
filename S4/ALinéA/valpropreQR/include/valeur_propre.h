#ifndef __VALEUR_PROPRE_H
#define __VALEUR_PROPRE_H

#include <stdio.h>
#include <stdlib.h>

#include "ALineA-TP1.h"
#include "ALineA-TP2.h"
#include "decomposition_QR.h"

#define EPSILON 0.0001
#define N 40000 //Nombre d'itération maximum
#define PAS 10 //Pas d'écriture de matrice dans le fichier (on écrit toutes les PAS matrices)

/*
 * Teste si a est égale à 0 (avec EPSILON de marche d'erreur)
 */
int estNulle(double a);


/*
 * 1 si a est triangulaire, 0 sinon
 */
int estTriangulaireSup(Matrix a);


/*
 * Met dans v le vecteur contenant les valeurs propres, et retourne le nombre d'itération nécéssaire
 */
int valeurPropre(Matrix a,Matrix * v);


/*
 * Met dans v le vecteur contenant les valeurs propres, et retourne le nombre d'itération nécéssaire. Ecrit dans filename la matrice de la Nieme itération
 */
void valeurPropre_gnuplot(Matrix a,char * filename);


/*
 * Ecrit la matrice dans le fichier : n'écrit que les coordonnées (inversé, comme pour tracer une fonction) des valeurs non nulle de la matrice
 */
void EcrireMatrice(Matrix a,FILE * file);

#endif
