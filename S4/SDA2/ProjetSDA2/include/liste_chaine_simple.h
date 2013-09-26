#ifndef __LISTE_CHAINE_SIMPLE_H
#define __LISTE_CHAINE_SIMPLE_H

#include <stdio.h>
#include <stdlib.h>

#define LISTE_RAND_MAX 5

typedef int S_LISTE_CHAINE_SIMPLE;

typedef struct StrListeElem { S_LISTE_CHAINE_SIMPLE val; struct StrListeElem * suiv;} StrListeElem, * ListeElem;
typedef struct StrListe {ListeElem t ; ListeElem q;int taille; }StrListe, *Liste;

Liste listenouv();
Liste adjt(Liste l,S_LISTE_CHAINE_SIMPLE a);
Liste supt(Liste l);
Liste adjq(Liste l,S_LISTE_CHAINE_SIMPLE a);
Liste supq(Liste l);
Liste remplacerIndice(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice);
S_LISTE_CHAINE_SIMPLE tete(Liste l);
S_LISTE_CHAINE_SIMPLE dernier(Liste l);
S_LISTE_CHAINE_SIMPLE ieme(Liste l,int i);
int estvide(Liste l);
int tailleliste(Liste l);
void afficherliste(Liste l);
Liste inserer(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice);
Liste supprIndice(Liste l,int indice);
Liste supprVal(Liste l,S_LISTE_CHAINE_SIMPLE a);
ListeElem adresseIeme(Liste l,int i);
Liste insav(Liste l,S_LISTE_CHAINE_SIMPLE a);
int indice(Liste l,S_LISTE_CHAINE_SIMPLE a);
int estdans(Liste l,S_LISTE_CHAINE_SIMPLE a);
void freeListe(Liste l);

Liste copieListe(Liste l);
Liste randomListeTrie(int n);

#endif

