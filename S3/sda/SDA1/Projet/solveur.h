/** \file
 * \author Thomas Kuntz
 * Solveur : Header
 * */

#ifndef __SOLVEUR_H
#define __SOLVEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorte.h"
#include "ensemble.h"
#include "matrice.h"
#include "graph.h"

extern int affichage;
extern int TAILLE_PIXEL;


/**
 * Calcule un taille de pixel adequat en fonction de la hauteur et largeur de la matrice à afficher
 * \param [in] l : entier, la largeur de la matrice à afficher
 * \param [in] h : entier, la hauteur de la matrice à afficher
 * \return un entier, la taille du pixel pour l'affichage de la matrice
 * \pre l>0
 * \pre h>0
 * \post
 */
int taillePixel(int h,int l);

/**
 * Boucle principale du programme de recherche de chemin
 * \param [in] m : Matrice, le pointeur de la StrMatrice du labyrinthe dont on doit chercher le chemin
 * \return le pointeur passé en parametre
 * \pre m doit avoir été initialisé et doit contenir un véritable labyrinthe
 * \post Affichage de la recherche (si activé)
 */
Matrice debut_recherche_naif(Matrice m);

/**
 * Première manière de choisir quel chemin prendre : regarde la case où l'on se trouve, et applique une préférence quant à la direction à prendre(si l'on ne vient pas de cette direction,et qu'il n'y a pas de mur): droite,puis bas,puis haut,puis gauche
 * \param [in] parcours : Ens, l'ensemble qui contient le parcours(Cad, le cheminement sans le retour depuis des culs de sac)
 * \param [in] dejavu : Ens, l'ensemble de toute les cases qu'on a déja vu(sur lesquelles ont est déjà passées)
 * \param [in] m : Matrice, la matrice du labyrinthe
 * \return un Couple, qui indique dans quel direction l'algorithme doit aller(contient un vecteur direction : exemple (0,1) correspond au bas)
 * \pre parcours doit avoir au moins un élément, et m doit contenir un labyrinthe conforme
 * \post
 */
Couple choisirchemin_A(Ens parcours,Ens dejavu,Matrice m);

/**
 * Deuxième manière de choisir le chemin à prendre : regarde depuis case où l'on se trouve les chemins possiblement prenable (c'est à dire pas là d'où on vient, ni la où on est déjà aller) et tire au hasard un de ces chemins
 * \param [in] parcours : Ens, l'ensemble qui contient le parcours(Cad, le cheminement sans le retour depuis des culs de sac)
 * \param [in] dejavu : Ens, l'ensemble de toute les cases qu'on a déja vu(sur lesquelles ont est déjà passées)
 * \param [in] m : Matrice, la matrice du labyrinthe
 * \return un Couple, qui indique dans quel direction l'algorithme doit aller(contient un vecteur direction : exemple (0,1) correspond au bas)
 * \pre parcours doit avoir au moins un élément, et m doit contenir un labyrinthe conforme
 * \post
 */
Couple choisirchemin_B(Ens parcours,Ens dejavu,Matrice m);

/**
 * Dessine tout les couples contenu dans l'ensemble donné en parametre, dans la couleur passé en parametre
 * \param [in] e : Ens, un ensemble de couple
 * \param [in] couleur : long, un couleur créée par la fonction newcolor()
 * \return
 * \pre les couples de l'ensemble doivent appartenir à la matrice (pas de dépassement de largeur/hauteur)
 * \pre couleur doit avoir été créé par newcolor()
 * \pre initgraph() doit avoir été appelé avant
 * \post les cases dont les coordonnées sont ceux des couples contenu dans \a e sont dessinées dans la conleur donnée
 */
void DessineEns(Ens e,long couleur);

/**
 * Dessine un couple dans la couleur indiqué
 * \param [in] c : Couple, coordonnée de la case à dessiner
 * \param [in] couleur : long, couleur dans laquel on doit dessiner la case
 * \return
 * \pre le couple doit appartenir à la matrice (pas de dépassement de largeur/hauteur)
 * \pre couleur doit avoir été créé par newcolor()
 * \pre initgraph() doit avoir été appelé avant
 * \post la couleur de la case dont les coordonnées sont ceux de \a c a changé pour la couleur en parametre
 */
void DessineCouple(Couple c,long couleur);

/**
 * Parcours et dessine les murs d'un labyrinthe dans la couleur indiquée
 * \param [in] m : Matrice, matrice du labyrinthe à dessiner
 * \param [in] couleur : long, couleur dans laquel les murs seront dessiner
 * \return
 * \pre couleur doit avoir été créé par newcolor()
 * \pre initgraph() doit avoir été appelé avant
 * \post Le labyrinthe a été dessiné
 */
void DessineLab(Matrice m,long couleur);

/**
 * Efface tout les couples de l'ensemble de l'affichage graphique(c'est à dire les redessiner en blanc)
 * \param [in] e : Ens, un ensemble de couple
 * \param [in] couleur : long, un couleur créée par la fonction newcolor()
 * \return
 * \pre les couples de l'ensemble doivent appartenir à la matrice (pas de dépassement de largeur/hauteur)
 * \pre couleur doit avoir été créé par newcolor()
 * \pre initgraph() doit avoir été appelé avant
 * \post les cases dont les coordonnées sont ceux des couples contenu dans \a e sont dessinées dans la conleur donnée
 */
void EffaceEns(Ens e);

/**
 * Efface un couple de l'affichage graphique(c'est à dire le redessine en blanc)
 * \param [in] c : Couple, coordonnée de la case à dessiner
 * \param [in] couleur : long, couleur dans laquel on doit dessiner la case
 * \return
 * \pre le couple doit appartenir à la matrice (pas de dépassement de largeur/hauteur)
 * \pre couleur doit avoir été créé par newcolor()
 * \pre initgraph() doit avoir été appelé avant
 * \post la couleur de la case dont les coordonnées sont ceux de \a c a changé pour la couleur en parametre
 */
void EffaceCouple(Couple c);

#endif
