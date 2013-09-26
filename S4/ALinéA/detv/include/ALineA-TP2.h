/** \file
 * Header : Fonction de calcul de déterminant/système linéaire
 **/

#ifndef __ALINEA_TP2_H
#define __ALINEA_TP2_H

#include <stdio.h>
#include <stdlib.h>

#include "ALineA-TP1.h"

/**
 * Fonction qui extrait une sous matrice de "m" et la met dans "mtmp", la sous matrice est 'm' sans la ligne i et colonne j.
 * \param [in] : Matrix m, La matrice dont on va extraire une sous matrice
 * \param [in] : Matrix mtmp, Une matrice de taille (m->nb_rows-1, m->nb_columns-1)
 * \param [in] : int i,j, La ligne et colonne ignoré pour la création de la sous matrice
 * \return Le pointeur sur la sous matrice(même que le pointeur donné en paramètre)
 * \post Les valeurs de mtmp forme une sous-matrice de m
 * \pre m et mtmp doivent être correctement allouées, 0<= i < m->nb_rows , 0<= j < m->nb_columns , 
 **/
Matrix extraction(Matrix m,Matrix mtmp,int i,int j);

/**
 * Fonction qui retourne la ligne du pivot(le plus grand élément en valeur absolu de la colonne) pour la triangularisation
 * \param [in] : Matrix m, Un pointeur sur une matrice
 * \param [in] : int i, la colonne dans laquelle on doit chercher le pivot
 * \return La ligne du pivot partiel
 * \pre m doit être correctement allouée, 0<= i < m->nb_columns
 **/
int pivotPartiel(Matrix m,int i);

/**
 * Echange les valeurs des lignes i et j de la matrice m
 * \param [in] : Matrix m, Un pointeur sur une matrice
 * \param [in] : int i,j, Les lignes à echanger
 * \return le pointeur de la matrice passé en paramètre
 * \post Les valeurs des lignes ont été échangées
 * \pre m doit être correctement alloué, 0<= i,j < m->nb_rows
 **/
Matrix switchLineMAtrix(Matrix m,int i,int j);

/**
 * Triangularise la matrice passé en argument
 * \param [in] : Matrix m, la matrice à triangulariser
 * \return (-1)^n, avec n le nombre d'echange de ligne effectué lors de la triangularisation
 * \post La matrice a été triangularisé
 * \pre m doit être correctement allouée
 **/
E triangulaire_det(Matrix m);

/**
 * Calcule le determinant de la matrice passé en paramètre de manière récursive
 * \param [in] : Matrix m, la matrice dont on calcule le determinant
 * \return Le déterminant de la matrice m
 * \pre m doit être correctement allouée
 **/
E m_determinant_rec(Matrix m);

/**
 * Calcule le determinant de la matrice passé en paramètre en triangularisant la matrice (attention à l'erreur de précision induite)
 * \param [in] : Matrix m, la matrice dont on calcule le determinant
 * \return Le déterminant de la matrice m
 * \pre m doit être correctement allouée
 **/
E m_determinant_triangle(Matrix m);

/**
 * Effectue la remonter du système ax=b
 * \param [in] : Matrix a, la matrice contenant le système dont on fait la remontée
 * \param [in] : Matrix b, la matrice résultat du système
 * \return La matrice x contenant les solutions du système
 * \post Allocation d'une matrice contenant les solutions du système
 * \pre 'a' doit être carré, triangulaire supérieur et ne pas avoir de 0 sur la diagonale
 **/
Matrix remontee(Matrix a,Matrix b);

/**
 * Calcul les solutions du système ax=b, en effectuant une triangularisation sur a et b, puis une remontée
 * \param [in] : Matrix a
 * \param [in] : Matrix b
 * \return La matrix x, contenant les solutions du système ax=b, ou NULL si aucune solution unique pour le système ne peut être trouvé
 * \post Une matrice pour x a été allouée
 * \pre a et b doivent être correctement allouées
 **/
Matrix m_gauss(Matrix a,Matrix b);

/**
 * Triangularise la matrice a passé en argument, en effectuant les mêmes opérations sur la matrice b(en vue d'une remontée)
 * \param [in] : Matrix a, la matrice à triangulariser
 * \param [in] : Matrix b, La matrice résultat à triangulariser
 * \return Retourne 0 si lors de la recherche de pivot il est impossible d'en trouver un non nul (matrice non inversible, donc solution non unique), 1 sinon
 * \post La matrice a et b ont été triangularisé
 * \pre a et b doivent être correctement allouées
 **/
E triangulaire_gauss(Matrix a,Matrix b);

#endif
