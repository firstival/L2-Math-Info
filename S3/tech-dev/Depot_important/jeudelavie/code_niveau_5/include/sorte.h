/** \file
 * \author Thomas Kuntz
 * Sorte : Header
 * */

#ifndef __SORTE_H
#define __SORTE_H

#define True 1
#define False 0
/** \struct Couple
 * Type Couple, qui contient deux entier,x et y, qui sont des coordonnées*/
typedef struct
{
	int x;/**<Abscisse*/
	int y;/**<Ordonnée*/
} Couple, * pCouple;


/** \memberof Couple
 * Constructeur : prend en entrée deux entiers, et construit un type Couple
 * \param [in] x : un entier
 * \param [in] y : un entier
 * \return un Couple
 * \pre
 * \post
 */
Couple construCouple(int x,int y);

/** \memberof Couple
 * Compare deux couples
 * \param [in] c1 : Couple
 * \param [in] c2 : Couple
 * \return 0 si les couples sont identiques, 1 sinon
 * \pre
 * \post
 */
int compareCouple(Couple c1,Couple c2);

/** \memberof Couple
 * Constructeur : Fait l'addition de deux couples
 * \param [in] a : Couple
 * \param [in] b : Couple
 * \return un Couple dont le x est l'addition des x de a et b, idem pour y
 * \pre
 * \post
 */
Couple additionCouple(Couple a,Couple b);

/**
 * Renvoit -1 si x < 0, 0 si x=0, 1 si x>0
 * \param [in] x : int
 * \return -1,0 ou 1
 * \pre
 * \post
 */
int zeroOuUn(int x);


#endif
