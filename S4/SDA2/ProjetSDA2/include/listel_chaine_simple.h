#ifndef __LISTEL_CHAINE_SIMPLE_H
#define __LISTEL_CHAINE_SIMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include "liste_chaine_simple.h"

#define MIN 4
#define MAX 6

typedef Liste S_LISTEL_CHAINE_SIMPLE;

typedef struct StrListelElem { S_LISTEL_CHAINE_SIMPLE val; struct StrListelElem * suiv;} StrListelElem, * ListelElem;
typedef struct StrListel {ListelElem t ; ListelElem q;int taille; }StrListel, *Listel;

Listel listenouv_l();
Listel adjt_l(Listel l,S_LISTEL_CHAINE_SIMPLE a);
Listel supt_l(Listel l);
Listel adjq_l(Listel l,S_LISTEL_CHAINE_SIMPLE a);
Listel supq_l(Listel l);
Listel remplacerIndice_l(Listel l,S_LISTEL_CHAINE_SIMPLE a,int indice);
S_LISTEL_CHAINE_SIMPLE tete_l(Listel l);
S_LISTEL_CHAINE_SIMPLE dernier_l(Listel l);
S_LISTEL_CHAINE_SIMPLE ieme_l(Listel l,int i);
int estvide_l(Listel l);
int tailleliste_l(Listel l);
void afficherliste_l(Listel l);
Listel inserer_l(Listel l,S_LISTEL_CHAINE_SIMPLE a,int indice);
Listel supprIndice_l(Listel l,int indice);
Listel supprVal_l(Listel l,S_LISTEL_CHAINE_SIMPLE a);
ListelElem adresseIeme_l(Listel l,int i);
int indice_l(Listel l,S_LISTEL_CHAINE_SIMPLE a);
int estdans_l(Listel l,S_LISTEL_CHAINE_SIMPLE a);
void freeListe_l(Listel l);


Listel copieListe_l(Listel l);
Listel randomListeTrie_l(int n);

#endif

