#ifndef __ARBRE_BINAIRE_H
#define __ARBRE_BINAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include "sorte_arbre.h"
#include "liste_contigue_a.h"

Arbin newArbin();
Arbin e(Arbin a,ARBRE_BIN_S v,Arbin b);

Listea desd(Arbin a,Listea p);

ARBRE_BIN_S rac(Arbin a);
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
int appartient(Arbin a,ARBRE_BIN_S v);
int hauteur_noeud(Arbin a,ARBRE_BIN_S v);
Listea bordgauche(Arbin a);
Listea borddroit(Arbin a);
int locc(Arbin a);//vérifie qu'un arbre binaire est localement complet
void afficherArbre(Arbin a);
Arbin copieArbre(Arbin a);
void freeArbre(Arbin a);

#endif

