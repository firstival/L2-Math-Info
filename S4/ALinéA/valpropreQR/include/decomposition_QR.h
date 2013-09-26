#ifndef __DECOMPOSITION_QR_H
#define __DECOMPOSITION_QR_H

#include <stdio.h>
#include <stdlib.h>

#include "ALineA-TP1.h"
#include "ALineA-TP2.h"
#include <math.h>

typedef struct {Matrix q;Matrix r;} QR_t;


/*
 * Donne la norme du vecteur x (la matrice x doit être un vecteur : une seule colonne, 1/plusieurs ligne(s) )
 */
double norme(Matrix x);


/*
 * Créer une matrice identité de taille n
 */
Matrix MatriceIdentite(int n);


/*
 * Met une matrice sous forme de l'identité (1 sur la diagonale, 0 sur tout le reste)
 */
void remiseSousFormeIdentie(Matrix a);


/*
 * Extrait la sous matrice de longueur n,hauteur m, d'origine (i,j) de A
 */
Matrix ExtractionMatrix(Matrix A,int nc,int nl,int i,int j);


/*
 * Insère la matrice B dans la matrice A, tel que l'origine de B devient i(colonne) et j(ligne)
 */
void insertionMatriceDansMatrice(Matrix A,Matrix B,int i,int j);


/*
 * Extrait le vecteur X de la matrice en argument (la première colonne de la matrice)
 */
Matrix extract_vectorX(Matrix x);


/*
 * Calcule alpha=+ ou - la norme de x
 */
E alpha(Matrix x);


/*
 * Calcule u=x-alpha*e1, avec e1(1,0,0,....0)
 */
Matrix vecteurU(Matrix x);


/* 
 * Calcule v=x/(norme(x))
 */
Matrix vecteurV(Matrix u);


/*
 * Calcule la matrice Q à partir de v Q=I-2*v*transposé(v)
 */
Matrix Matrice_Q_aux(Matrix v);


/*
 * Calcule la matrice Qk, matrice de householder de la matrice A
 */
Matrix Matrice_Qk(Matrix A);


/*
 * Calcule la decomposition QR de la matrice a
 */
QR_t decompositionQR(Matrix a);


#endif
