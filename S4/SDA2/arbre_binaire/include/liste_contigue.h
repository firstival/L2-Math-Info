#ifndef __LISTE_CONTIGU_H
#define __LISTE_CONTIGU_H

#include <stdio.h>
#include <stdlib.h>
#include "sorte_arbre.h"

#define TAILLE_LISTE 50

typedef Arbin S_LISTE_CONTIGU;

typedef struct { S_LISTE_CONTIGU * tab; int taille;int taillemax;} Liste;

Liste listenouv();
Liste adjt(Liste l,S_LISTE_CONTIGU a);
Liste supt(Liste l);
Liste adjq(Liste l,S_LISTE_CONTIGU a);
Liste supq(Liste l);
Liste remplacerIndice(Liste l,S_LISTE_CONTIGU a,int indice);
S_LISTE_CONTIGU tete(Liste l);
S_LISTE_CONTIGU dernier(Liste l);
int estvide(Liste l);
int tailleliste(Liste l);
void afficherliste(Liste l);
Liste inserer(Liste l,S_LISTE_CONTIGU a,int indice);
Liste supprIndice(Liste l,int indice);
Liste supprVal(Liste l,S_LISTE_CONTIGU a);
int indice(Liste l,S_LISTE_CONTIGU a);
int estdans(Liste l,S_LISTE_CONTIGU a);
void freeListe(Liste l);



#endif

