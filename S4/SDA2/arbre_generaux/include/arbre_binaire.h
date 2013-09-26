#ifndef __ARBRE_BINAIRE_H
#define __ARBRE_BINAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include "sorte_arbre.h"
#include "liste_contigue.h"

Arbin newArbin();
Arbin e(Arbin a,S v,Arbin b);


S rac(Arbin a);
Arbin ag(Arbin a);
Arbin ad(Arbin a);
int vide(Arbin a);
int nn(Arbin a);
int nf(Arbin a);
int ni(Arbin a);
int hauteur(Arbin a);
Arbin extr_g(Arbin a);
Arbin extr_d(Arbin a);
int f(Arbin a);
int appartient(Arbin a,S v);
int hauteur_noeud(Arbin a,S v);
Liste bordgauche(Arbin a);
Liste borddroit(Arbin a);
int locc(Arbin a);//vérifie qu'un arbre binaire est localement complet
void afficherArbre(Arbin a);
//~ int lc(Arbin a);//longueur de cheminement externe,interne,total d'un arbre binaire
//~ int lci(Arbin a);
//~ int lce(Arbin a);
//int eval(Arbin a);


#endif

