/** \file
 * \author Thomas Kuntz
 * Constructeur : Header
 * */

#ifndef __CONSTRUCTEUR_H
#define __CONSTRUCTEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorte.h"
#include "ensemble.h"
#include "matrice.h"
#include "graph.h"

#define INTER 20

extern int TAILLE_PIXEL;
extern int affichage_generation;
extern int affichage_cases_constructibles;

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
 * Boucle principale de la construction : construit des murs de l'ensemble de mur constructible tant qu'il y en a
 * \param [in] m : Matrice, la matrice dans laquel on va construire le labyrinthe
 * \return m, la matrice construite du labyrinthe
 * \pre m doit avoir été initialisé par MatAlloc()
 * \post la matrice est labyrinthe,les murs sont des "True", le reste est "False"
 */
Matrice debut_generation(Matrice m);

/**
 * Construit des murs "True" sur les contours de la matrice
 * \param [in] m : Matrice, matrice sur laquel on va poser les murs autours
 * \param [in] e : Ens, Un ensemble de mur dans lequel on va stocker les coordonnées des murs que l'on va construire
 * \return \a e, qui contient alors les coordonnées des murs que la fonction à construit
 * \pre \a m doit avoir été initalisée par MatAlloc()
 * \pre \a e doit avoir été initialisée par EnsAlloc()
 * \post les contours de \a m ont été changé à "True"
 */
Ens emmurement(Matrice m,Ens e);

/**
 * Recherche la graine responsable d'une case constructible
 * \param [in] m : Matrice, la matrice du labyrinthe
 * \param [in] c : Couple, les coordonnées de la case constructible
 * \return les coordonnées de la graine responsable de la case constructible donnée en parametre
 * \pre \a c doit obligatoirement être constructible, c'est à dire ne pas avoir plusieurs mur déjà construits adjacents
 * \post \a m doit avoir été initialisé par MatAlloc()
 */
Couple recherche_seed_mur_constructible(Matrice m,Couple c);

/**
 * Teste si une case est constructible
 * \param [in] c : Couple, coordonnée de la case à tester
 * \param [in] m : Matrice, matrice du labyrinthe en construction
 * \return un entier, 0 si \a c n'est pas constructible, 1 si elle est constructible
 * \pre \a m  doit avoir été initialisé par MatAlloc()
 * \post
 */
int EstConstructible(Matrice m,Couple c);

/**
 * Initialise l'ensemble des graines, et les construit dans \a m
 * \param [in] m : Matrice, matrice du labyrinthe
 * \return un Ens qui contient les coordonnées des graines
 * \pre \a m doit avoir été initialisé par MatAlloc()
 * \post Les graines ont été construite dans \a m, un ensemble a été alloué
 */
Ens initEns_seed(Matrice m);

/**
 * Initialise un ensemble de mur constructible à partir d'un ensemble de graine
 * \param [in] e : Ens, ensemble de graine
 * \param [in] m : Matrice, matrice du labyrinthe
 * \return un Ens qui contient les coordonnées des murs constructibles trouvées à partir de l'ensemble des graines
 * \pre \a m doit avoir été initalisée par MatAlloc()
 * \pre \a e doit avoir été initialisée par EnsAlloc()
 * \pre 10<m->h et 10<m->l
 * \post Un ensemble a été alloué
 */
Ens initEns_murConstructible(Ens e,Matrice m);

/**
 * Supprime de l'ensemble de mur constructible les cases autours d'un mur nouvellement construit, et les effaces(dessine en blanc) de l'affichage(si affichage activé)
 * \param [in] c : Couple, Coordonnées de mur nouvellement construit
 * \param [in] m : Matrice, matrice du labyrinthe
 * \return L'ensemble des murs constructibles
 * \pre \a m doit avoir été initalisée par MatAlloc()
 * \pre \a emc doit avoir été initialisée par EnsAlloc()
 * \post Les Couples autours de \a c ont été retirée de de \a emc, l'ensemble des murs constructibles
 * \post Efface les murs que l'on enlève de l'ensemble de l'affichage
 */
Ens SupprMurPlusConstructible(Couple c,Ens emc,Matrice m);

/**
 * Ajoute les murs constructibles générées par un mur nouvellement construit à l'ensemble des murs constructibles, dessine(si affichage activé) ces murs de la couleur passé en parametre
 * \param [in] c : Couple, les coordonnées de mur nouvellement construit
 * \param [in] emc : Ens, ensemble de murs constructibles
 * \param [in] m : Matrice, matrice du labyrinthe en construction
 * \param [in] couleur : long, couleur dans laquel on doit afficher les nouvelles cases constructibles
 * \return ensemble des murs constructibles mis à jour
 * \pre \a m doit avoir été initalisée par MatAlloc()
 * \pre \a emc doit avoir été initialisée par EnsAlloc()
 * \post \a emc a été mis à jour avec les nouveaux murs constructibles générés par \a c
 * \post Affiche les nouveaux mur constructibles dans la couleur passé en paramètre(si l'affichage est activé)
 */
Ens AjoutNouveauxMursConstructibles(Couple c,Ens emc,Matrice m,long couleur);

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
