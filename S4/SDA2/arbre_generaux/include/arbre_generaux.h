#ifndef ARBRE__GENERAUX_H
#define ARBRE__GENERAUX_H

#include <stdio.h>
#include <stdlib.h>
#include "arbre_binaire.h"
#include "liste_contigue.h"

Liste desg(Arbin a,Liste p);
Arbin ge(S x);// arbre réduit à une feuille
Arbin i(Arbin ap,Arbin af,S x);//insertion d'un arbre comme kieme fils d'un autre
Arbin fils(Arbin a,int k);//donnant le kième sous arbre
int ef(Arbin a);// testant si l'arbre est une feuilles
S racine(Arbin a);//racine
int nb_fils(Arbin a);//nombre de fils
int nb_noeud(Arbin a);
int h(Arbin a);

int max(int a,int b);







#endif
