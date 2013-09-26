/** \file
 * Header : Fonction sur les Matrices du TP1
 **/
#ifndef __ALINEA_TP1_H
#define __ALINEA_TP1_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Nombre maximum des aij des matrices lors de création aléatoire de matrice
#define RANDOM_NUMBER 10

typedef double E;
typedef struct matrix { E * mat; /**< Pointeur sur un tableau de type E qui représente la matrice */
						int nb_rows,/**< Nombre de ligne de la matrice */
						nb_columns;/**< Nombre de colonne de la matrice */
						}StrMatrix, *Matrix;

/**
 * Alloue une matrice avec le nombre de ligne et colonne indiqué
 * \param [in] : int nb_rows, le nombre de ligne de la matrice
 * \param [in] : int nb_columns, le nombre de colonne de la matrice
 * \return Un pointeur sur un StrMatrix de la taille indiqué
 * \post Allocation en mémoire d'un StrMatrix et d'un tableau de nb_rows*nb_columns type E
 * \pre nb_rows > 0, nb_columns > 0
 **/
Matrix newMatrix(int nb_rows,int nb_columns);
/**
 * Selecteur : renvoie la valeur de la case aij, avec i=row,j=column
 * \param [in] : int row, la ligne de l'élément demandé
 * \param [in] : int column, la colonne de l'élément demandé
 * \return La valeur de l'élément demandé
 * \pre 0 <= row < m->nb_rows, 0 <= column < m->nb_columns
 **/
E getElt(Matrix m,int row,int column);
/**
 * Mutateur : Change la valeur de la case aij, avec i=row, j=column
 * \param [in] : int row, la ligne de l'élément à changer
 * \param [in] : int column, la colonne de l'élément à changer
 * \post La valeur de aij a changé
 * \pre 0 <= row < m->nb_rows, 0 <= column < m->nb_columns
 **/
void setElt(Matrix m,int row,int column,E val);
/**
 * Désalloue une Matrice
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \post La Matrice est désallouée
 **/
void deleteMatrix(Matrix m);
/**
 * Teste si une matrice est carré
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return 0 si la matrice n'est pas carré, 1 sinon
 * \pre m doit être correctement alloué
 **/
int isSquare(Matrix m);
/**
 * Teste si une matrice est symetrique
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return 0 si la matrice n'est pas symetrique, 1 sinon
 * \pre m doit être correctement allouée
 **/
int isSymetric(Matrix m);
/**
 * Calcule et renvoie la transposé de la matrice passé en argument
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return La transposé de la matrice
 * \post La transposé de m a été alloué en mémoire
 * \pre m doit être correctement allouée
 **/
Matrix transpose(Matrix m);
/**
 * Additionne deux matrice
 * \param [in] : Matrix m1, un pointeur sur une matrice
 * \param [in] : Matrix m2, un pointeur sur une matrice
 * \return La somme des deux matrices passé en argument
 * \post La matrice résultante de la somme de celles passé en argument a été alloué
 * \pre m1 et m2 doivent avoir été correctement allouées
 **/
Matrix addition(Matrix m1,Matrix m2);
/**
 * Soustrait deux matrice
 * \param [in] : Matrix m1, un pointeur sur une matrice
 * \param [in] : Matrix m2, un pointeur sur une matrice
 * \return La soustraction des deux matrices passé en argument
 * \post La matrice résultante de la soustraction de celles passé en argument a été alloué
 * \pre m1 et m2 doivent avoir été correctement allouées
 **/
Matrix soustraction(Matrix m1,Matrix m2);
/**
 * Fait le produit de deux matrice
 * \param [in] : Matrix m1, un pointeur sur une matrice
 * \param [in] : Matrix m2, un pointeur sur une matrice
 * \return Le produit des deux matrices passé en argument
 * \post La matrice résultante du produit de celles passé en argument a été alloué
 * \pre m1 et m2 doivent avoir été correctement allouées
 **/
Matrix multiplication(Matrix m1,Matrix m2);
/**
 * Multiplie tout les éléments d'une matrice par un scalaire
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \param [in] : E x, le scalaire
 * \return Le pointeur sur la matrice dont les éléments ont été multiplié par le scalaire
 * \post Les éléments de la matrice on été multiplié par le scalaire
 * \pre m1 doit être correctement allouée
 **/
Matrix mult_scalar(E x,Matrix m1);
/**
 * Affiche une matrice sur la sortie standard
 * \param [in] : Matrix m, un pointeur sur la matrice à afficher
 * \post Affichage des éléments de la matrice
 * \pre m doit être correctement alloué
 **/
void displayMatrix(Matrix m);
/**
 * Effecture une combinaison linéaire avec deux lignes de la matrice, line2=scal2*line2 + scal1*line1
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \param [in] : int line1, line2, indices des lignes dont on va faire la combinaison linéaire
 * \param [in] : E scal1,scal2, valeur des scalaires utilisés dans la combinaison linéaire
 * \return Un pointeur sur la matrice passé en argument dont on a effectué une combinaison linéaire avec les lignes et scalaire indiqués
 * \post La valeur de la line2 ont changé
 * \pre m doit être correctement allouée, 0<= line1,line2 < m->nb_rows
 **/
Matrix linearComb(Matrix m,int line1,int line2,E scal1,E scal2);
/**
 * Remplie la matrice de nombre au hasard
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return La matrice remplie de nombre aléatoire
 * \post La valeur des cases de la matrice ont changé
 * \pre m doit être correctement allouée
 **/
Matrix randomMatrix(Matrix m);
/**
 * Fonction qui permet de saisir sa propre matrice
 * \return La matrice que l'utilisateur a voulu
 * \post Une matrice a été alloué en mémoire
 **/
Matrix saisirMatrix();
/**
 * Copie une matrice
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return un pointeur sur une autre matrice qui est une copie de celle passé en argument
 * \post Allocation d'une matrice identique à celle passé en argument
 * \pre m doit être correctement alloué
 **/
Matrix copieMatrix(Matrix m);

#endif
