/** \file
 * \author Thomas Kuntz
 * Ensemble : Header
 * */

#ifndef __ENSEMBLE_H
#define __ENSEMBLE_H

#include <stdio.h>
#include <stdlib.h>

#include "sorte.h"

#define MAXENS 50
/** \struct StrEns
 * Structure StrEns,avec Ens un pointeur sur un StrEns */
typedef struct
{
	pCouple tab;/**< pointeur pour un tableau de Couple*/
	int taille;/**< Nombre d'élément dans l'ensemble */
	int taillemax;/**< taille maximum de l'ensemble */
} StrEns, * Ens;

/** \memberof StrEns
 * Alloue un ensemble
 * \return un Ens, pointeur sur l'ensemble alloué
 * \pre
 * \post un StrEns a été alloué en mémoire
 */
Ens EnsAlloc();

/** \memberof StrEns
 * Désalloue un ensemble
 * \param [in] E : Ens, un pointeur sur un StrEns
 * \return
 * \pre
 * \post l'ensemble pointé par E ne doit plus être utilisé, car \a E a été désalloué
 */
void EnsFree(Ens E);

/** \memberof StrEns
 * Test de vacuité sur \a E
 * \param [in] E: Ens, un pointeur sur un ensemble
 * \return 0 si l'ensemble est vide, 1 sinon
 * \pre \a E != NULL
 * \post
 */
int EnsEstVide(Ens E);

/** \memberof StrEns
 * Ajoute un couple à l'ensemble
 * \param [in] E : Ens, un ensemble
 * \param [in] c : Couple, le couple à ajouter
 * \return un ensemble dont on a ajouté \a c
 * \pre \a E != NULL
 * \post Si il n'y avait plus assez de place dans l'ensemble, on a alloué un nouveau tableau de taille taillemax+MAXENS
 * \post on a ajouté un élément à l'ensemble
 */
Ens EnsAjoute(Ens E,Couple c);

/** \memberof StrEns
 * Recherche un Couple dans un ensemble
 * \param [in] E : Ens, l'ensemble dans lequel on doit chercher le couple
 * \param [in] c : Couple, le Couple à chercher
 * \return -1 si le Couple n'est pas présent dans l'ensemble, la place de ce Couple dans le tableau de l'ensemble sinon
 * \pre \a E != NULL
 * \post
 */
int EnsRechercheCouple(Ens E,Couple c);

/** \memberof StrEns
 * Suprimme le ième élément de l'ensemble
 * \param [in] E : Ens, l'ensemble dans lequel on doit supprimer l'élément
 * \param [in] i : int, l'indice de l'élément à supprimer
 * \return l'ensemble dans lequel on a supprimé le ième élément
 * \pre \a E != NULL
 * \pre 0<= i < E.taille
 * \post l'élément à l'indice (E.Taille-1) a été mis à la place du ième élément
 * \post la taille de l'ensemble à été réduite de 1
 */
Ens SupprIeme(Ens E,int i);

/** \memberof StrEns
 * Supprime de l'ensemble le Couple passé en argument
 * \param [in] E : Ens, l'ensemble dans lequel on va supprimer le couple
 * \param [in] c : Couple, le Couple à supprimer
 * \return L'ensemble dans lequel on a supprimé \a c
 * \pre \a E != NULL
 * \post Si \a c était dans \a E, alors il est supprimé de l'ensemble
 */
Ens EnsSuppr(Ens E,Couple c);

/** \memberof StrEns
 * Supprime le dernier élément de l'ensemble
 * \param [in] E : Ens, l'ensemble dont on va supprimer le dernier élément
 * \return L'ensemble dont on a supprimé le dernier élément
 * \pre \a E !=NULL
 * \post La taille de \a E a été réduite de 1
 */
Ens EnsSupprDernier(Ens E);

/** \memberof StrEns
 * Teste si un Couple appartient à l'ensemble passé en paramètre
 * \param [in] E : Ens, l'ensemble que l'on va testé
 * \param [in] c : Couple, le couple que l'on va chercher
 * \return 1 si \a c est dans E, 0 sinon
 * \pre \a E !=NULL
 * \post
 */
int EnsEstDans(Ens E,Couple c);

/** \memberof StrEns
 * Donne le nombre d'élément dans l'ensemble
 * \param [in] E : Ens
 * \return la taille de l'ensemble
 * \pre \a E != NULL
 * \post
 */
int EnsTaille(Ens E);

/** \memberof StrEns
 * Tire un couple aléatoirement dans l'ensemble, le retire de l'ensemble
 * \param [in] E : Ens
 * \return le Couple tiré par la fonction
 * \pre \a E != NULL
 * \post le couple tiré supprimé de l'ensemble
 */
Couple EnsTirage(Ens E);

#endif
