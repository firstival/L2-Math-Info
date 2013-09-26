#ifndef __LISTE_CONTIGU_H
#define __LISTE_CONTIGU_H

#include <stdio.h>
#include <stdlib.h>

#define TAILLE_LISTE 50
#define LISTE_RAND_MAX 50


typedef int S_LISTE_CONTIGU;

typedef struct { S_LISTE_CONTIGU * tab; int taille;int taillemax;}StrListe, * Liste;

Liste listenouv();
Liste adjt(Liste l,S_LISTE_CONTIGU a);
Liste supt(Liste l);
Liste adjq(Liste l,S_LISTE_CONTIGU a);
Liste supq(Liste l);
Liste remplacerIndice(Liste l,S_LISTE_CONTIGU a,int indice);
S_LISTE_CONTIGU tete(Liste l);
S_LISTE_CONTIGU dernier(Liste l);
Liste concat(Liste l1,Liste l2);
S_LISTE_CONTIGU ieme(Liste l,int i);
int estvide(Liste l);
int tailleliste(Liste l);
void afficherliste(Liste l);
Liste inserer(Liste l,S_LISTE_CONTIGU a,int indice);
Liste supprIndice(Liste l,int indice);
Liste supprVal(Liste l,S_LISTE_CONTIGU a);
int indice(Liste l,S_LISTE_CONTIGU a);
int estdans(Liste l,S_LISTE_CONTIGU a);
void freeListe(Liste l);

Liste randomListe(int n);

#endif

