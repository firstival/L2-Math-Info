/** \file
 * Header : Fonction de calcul de d�terminant/syst�me lin�aire
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
 * \param [in] : int i,j, La ligne et colonne ignor� pour la cr�ation de la sous matrice
 * \return Le pointeur sur la sous matrice(m�me que le pointeur donn� en param�tre)
 * \post Les valeurs de mtmp forme une sous-matrice de m
 * \pre m et mtmp doivent �tre correctement allou�es, 0<= i < m->nb_rows , 0<= j < m->nb_columns , 
 **/
Matrix extraction(Matrix m,Matrix mtmp,int i,int j);

/**
 * Fonction qui retourne la ligne du pivot(le plus grand �l�ment en valeur absolu de la colonne) pour la triangularisation
 * \param [in] : Matrix m, Un pointeur sur une matrice
 * \param [in] : int i, la colonne dans laquelle on doit chercher le pivot
 * \return La ligne du pivot partiel
 * \pre m doit �tre correctement allou�e, 0<= i < m->nb_columns
 **/
int pivotPartiel(Matrix m,int i);

/**
 * Echange les valeurs des lignes i et j de la matrice m
 * \param [in] : Matrix m, Un pointeur sur une matrice
 * \param [in] : int i,j, Les lignes � echanger
 * \return le pointeur de la matrice pass� en param�tre
 * \post Les valeurs des lignes ont �t� �chang�es
 * \pre m doit �tre correctement allou�, 0<= i,j < m->nb_rows
 **/
Matrix switchLineMAtrix(Matrix m,int i,int j);

/**
 * Triangularise la matrice pass� en argument
 * \param [in] : Matrix m, la matrice � triangulariser
 * \return (-1)^n, avec n le nombre d'echange de ligne effectu� lors de la triangularisation
 * \post La matrice a �t� triangularis�
 * \pre m doit �tre correctement allou�e
 **/
E triangulaire_det(Matrix m);

/**
 * Calcule le determinant de la matrice pass� en param�tre de mani�re r�cursive
 * \param [in] : Matrix m, la matrice dont on calcule le determinant
 * \return Le d�terminant de la matrice m
 * \pre m doit �tre correctement allou�e
 **/
E m_determinant_rec(Matrix m);

/**
 * Calcule le determinant de la matrice pass� en param�tre en triangularisant la matrice (attention � l'erreur de pr�cision induite)
 * \param [in] : Matrix m, la matrice dont on calcule le determinant
 * \return Le d�terminant de la matrice m
 * \pre m doit �tre correctement allou�e
 **/
E m_determinant_triangle(Matrix m);

/**
 * Effectue la remonter du syst�me ax=b
 * \param [in] : Matrix a, la matrice contenant le syst�me dont on fait la remont�e
 * \param [in] : Matrix b, la matrice r�sultat du syst�me
 * \return La matrice x contenant les solutions du syst�me
 * \post Allocation d'une matrice contenant les solutions du syst�me
 * \pre 'a' doit �tre carr�, triangulaire sup�rieur et ne pas avoir de 0 sur la diagonale
 **/
Matrix remontee(Matrix a,Matrix b);

/**
 * Calcul les solutions du syst�me ax=b, en effectuant une triangularisation sur a et b, puis une remont�e
 * \param [in] : Matrix a
 * \param [in] : Matrix b
 * \return La matrix x, contenant les solutions du syst�me ax=b, ou NULL si aucune solution unique pour le syst�me ne peut �tre trouv�
 * \post Une matrice pour x a �t� allou�e
 * \pre a et b doivent �tre correctement allou�es
 **/
Matrix m_gauss(Matrix a,Matrix b);

/**
 * Triangularise la matrice a pass� en argument, en effectuant les m�mes op�rations sur la matrice b(en vue d'une remont�e)
 * \param [in] : Matrix a, la matrice � triangulariser
 * \param [in] : Matrix b, La matrice r�sultat � triangulariser
 * \return Retourne 0 si lors de la recherche de pivot il est impossible d'en trouver un non nul (matrice non inversible, donc solution non unique), 1 sinon
 * \post La matrice a et b ont �t� triangularis�
 * \pre a et b doivent �tre correctement allou�es
 **/
E triangulaire_gauss(Matrix a,Matrix b);

#endif
