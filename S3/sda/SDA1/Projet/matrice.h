/** \file
 * \author Thomas Kuntz
 * Matrice : Header
 * */

#ifndef __MATRICE_H
#define __MATRICE_H

#include <stdio.h>
#include <stdlib.h>
#include "sorte.h"

/** typedef pour éviter d'écrire unsigned char à chaque fois */
typedef unsigned char Bool;

/** \struct StrMatrice
 *  Structure StrMatrice, avec Matrice pointeur sur StrMatrice */
typedef struct
{
	Bool ** tab;/**< pointeur de pointeur, qui pointera sur le tableau de tableau qui représente la matrice */
	int h;/**< hauteur de la matrice*/
	int l;/**< largeur de la matrice*/
} StrMatrice, * Matrice;


typedef Matrice (*fct_matrice) (Matrice);

/** \memberof StrMatrice
 * Création d'une nouvelle matrice \a h *\a l initialisé à False
 * \param [in] h : int, la hauteur de la matrice
 * \param [in] l : int, la largeur de la matrice
 * \return une Matrice, pointeur sur la StrMatrice alloué
 * \pre 0<l , 0<h
 * \post un table h*l a été alloué
 */
Matrice MatAlloc(int h,int l);

/** \memberof StrMatrice
 * Libération de la mémoire utilisé par la matrice
 * \param [in] m : Matrice
 * \return
 * \pre
 * \post \a m ne doit plus être utilisé, car il a été désalloué
 */
void MatFree(Matrice m);

/** \memberof StrMatrice
 * Renvoie la valeur booléenne de la matrice aux coordonnées passé par le Couple en argument
 * \param [in] m : Matrice
 * \param [in] c : Couple, coordoonné de la case à évaluer
 * \return False ou True, selon la valeur contenant dans la matrice
 * \pre 0<=c.x< m->l
 * \pre 0<=c.y< m->h
 * \post
 */
Bool MatVal(Matrice m,Couple c);

/** \memberof StrMatrice
 * Stocke une valeur booléenne dans la matrice aux coordonnées données par le Couple passé en argument
 * \param [in] m : Matrice
 * \param [in] c : Couple, coordoonnées de la case à modifier
 * \param [in] val : Bool, la valeur booléenne à stocker
 * \return la matrice dont on a changé la case (c.x,c.y) pour \a val
 * \pre 0<=c.x< m->l
 * \pre 0<=c.y< m->h
 * \post m->tab[c.x][c.y] a changé
 */
Matrice MatSet(Matrice m,Couple c,Bool val);

/** \memberof StrMatrice
 * Compte le nombre de mur d'un labyrinthe
 * \param [in] m : Matrice, la matrice dont on va compter les murs
 * \return le nombre de mur de \a m
 * \pre m!=NULL
 * \post
 */
int CompteTrue(Matrice m);

/** \memberof StrMatrice
 * Enregistre une matrice dans un fichier, attention, si on lui donne le même nom à chaque fois, il ecrasera ce fichier pour ecrire le nouveau
 * \param [in] m : Matrice, la matrice à enregistrer
 * \param [in] nom_fichier : char *, nom du fichier sous lequel on va enregistrer la matrice
 * \return 1 si l'enregistrement s'est bien passé, 0 sinon
 * \pre m!=NULL
 * \pre nom_fichier != NULL
 * \pre
 * \post la matrice a été sauvegardé dans le fichier \a nom_fichier
 */
int MatSauve(Matrice m, char * nom_fichier);

/** \memberof StrMatrice
 * Lit une matrice depuis un fichier
 * \param [in] nom_fichier : char *, nom du fichier duquel on va lire la matrice
 * \return une matrice créée depuis le fichier \a nom_fichier
 * \pre nom_fichier != NULL
 * \post Allocation d'une matrice depuis le fichier \a nom_fichier
 */
Matrice MatLit(char * fichier);


#endif
