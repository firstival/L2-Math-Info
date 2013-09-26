/** \file
 * Header : Fonction sur les Matrices du TP1
 **/
#ifndef __ALINEA_TP1_H
#define __ALINEA_TP1_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Nombre maximum des aij des matrices lors de cr�ation al�atoire de matrice
#define RANDOM_NUMBER 10

typedef double E;
typedef struct matrix { E * mat; /**< Pointeur sur un tableau de type E qui repr�sente la matrice */
						int nb_rows,/**< Nombre de ligne de la matrice */
						nb_columns;/**< Nombre de colonne de la matrice */
						}StrMatrix, *Matrix;

/**
 * Alloue une matrice avec le nombre de ligne et colonne indiqu�
 * \param [in] : int nb_rows, le nombre de ligne de la matrice
 * \param [in] : int nb_columns, le nombre de colonne de la matrice
 * \return Un pointeur sur un StrMatrix de la taille indiqu�
 * \post Allocation en m�moire d'un StrMatrix et d'un tableau de nb_rows*nb_columns type E
 * \pre nb_rows > 0, nb_columns > 0
 **/
Matrix newMatrix(int nb_rows,int nb_columns);
/**
 * Selecteur : renvoie la valeur de la case aij, avec i=row,j=column
 * \param [in] : int row, la ligne de l'�l�ment demand�
 * \param [in] : int column, la colonne de l'�l�ment demand�
 * \return La valeur de l'�l�ment demand�
 * \pre 0 <= row < m->nb_rows, 0 <= column < m->nb_columns
 **/
E getElt(Matrix m,int row,int column);
/**
 * Mutateur : Change la valeur de la case aij, avec i=row, j=column
 * \param [in] : int row, la ligne de l'�l�ment � changer
 * \param [in] : int column, la colonne de l'�l�ment � changer
 * \post La valeur de aij a chang�
 * \pre 0 <= row < m->nb_rows, 0 <= column < m->nb_columns
 **/
void setElt(Matrix m,int row,int column,E val);
/**
 * D�salloue une Matrice
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \post La Matrice est d�sallou�e
 **/
void deleteMatrix(Matrix m);
/**
 * Teste si une matrice est carr�
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return 0 si la matrice n'est pas carr�, 1 sinon
 * \pre m doit �tre correctement allou�
 **/
int isSquare(Matrix m);
/**
 * Teste si une matrice est symetrique
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return 0 si la matrice n'est pas symetrique, 1 sinon
 * \pre m doit �tre correctement allou�e
 **/
int isSymetric(Matrix m);
/**
 * Calcule et renvoie la transpos� de la matrice pass� en argument
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return La transpos� de la matrice
 * \post La transpos� de m a �t� allou� en m�moire
 * \pre m doit �tre correctement allou�e
 **/
Matrix transpose(Matrix m);
/**
 * Additionne deux matrice
 * \param [in] : Matrix m1, un pointeur sur une matrice
 * \param [in] : Matrix m2, un pointeur sur une matrice
 * \return La somme des deux matrices pass� en argument
 * \post La matrice r�sultante de la somme de celles pass� en argument a �t� allou�
 * \pre m1 et m2 doivent avoir �t� correctement allou�es
 **/
Matrix addition(Matrix m1,Matrix m2);
/**
 * Soustrait deux matrice
 * \param [in] : Matrix m1, un pointeur sur une matrice
 * \param [in] : Matrix m2, un pointeur sur une matrice
 * \return La soustraction des deux matrices pass� en argument
 * \post La matrice r�sultante de la soustraction de celles pass� en argument a �t� allou�
 * \pre m1 et m2 doivent avoir �t� correctement allou�es
 **/
Matrix soustraction(Matrix m1,Matrix m2);
/**
 * Fait le produit de deux matrice
 * \param [in] : Matrix m1, un pointeur sur une matrice
 * \param [in] : Matrix m2, un pointeur sur une matrice
 * \return Le produit des deux matrices pass� en argument
 * \post La matrice r�sultante du produit de celles pass� en argument a �t� allou�
 * \pre m1 et m2 doivent avoir �t� correctement allou�es
 **/
Matrix multiplication(Matrix m1,Matrix m2);
/**
 * Multiplie tout les �l�ments d'une matrice par un scalaire
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \param [in] : E x, le scalaire
 * \return Le pointeur sur la matrice dont les �l�ments ont �t� multipli� par le scalaire
 * \post Les �l�ments de la matrice on �t� multipli� par le scalaire
 * \pre m1 doit �tre correctement allou�e
 **/
Matrix mult_scalar(E x,Matrix m1);
/**
 * Affiche une matrice sur la sortie standard
 * \param [in] : Matrix m, un pointeur sur la matrice � afficher
 * \post Affichage des �l�ments de la matrice
 * \pre m doit �tre correctement allou�
 **/
void displayMatrix(Matrix m);
/**
 * Effecture une combinaison lin�aire avec deux lignes de la matrice, line2=scal2*line2 + scal1*line1
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \param [in] : int line1, line2, indices des lignes dont on va faire la combinaison lin�aire
 * \param [in] : E scal1,scal2, valeur des scalaires utilis�s dans la combinaison lin�aire
 * \return Un pointeur sur la matrice pass� en argument dont on a effectu� une combinaison lin�aire avec les lignes et scalaire indiqu�s
 * \post La valeur de la line2 ont chang�
 * \pre m doit �tre correctement allou�e, 0<= line1,line2 < m->nb_rows
 **/
Matrix linearComb(Matrix m,int line1,int line2,E scal1,E scal2);
/**
 * Remplie la matrice de nombre au hasard
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return La matrice remplie de nombre al�atoire
 * \post La valeur des cases de la matrice ont chang�
 * \pre m doit �tre correctement allou�e
 **/
Matrix randomMatrix(Matrix m);
/**
 * Fonction qui permet de saisir sa propre matrice
 * \return La matrice que l'utilisateur a voulu
 * \post Une matrice a �t� allou� en m�moire
 **/
Matrix saisirMatrix();
/**
 * Copie une matrice
 * \param [in] : Matrix m, un pointeur sur une matrice
 * \return un pointeur sur une autre matrice qui est une copie de celle pass� en argument
 * \post Allocation d'une matrice identique � celle pass� en argument
 * \pre m doit �tre correctement allou�
 **/
Matrix copieMatrix(Matrix m);

#endif
