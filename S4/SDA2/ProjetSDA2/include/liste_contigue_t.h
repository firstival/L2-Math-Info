#ifndef __LISTE_CONTIGU_T_H
#define __LISTE_CONTIGU_T_H

#include <stdio.h>
#include <stdlib.h>
#include "sorte_tournoi_position.h"

#define TAILLE_LISTE 50

typedef TournoiBinPos S_LISTE_T_CONTIGU;

typedef struct { S_LISTE_T_CONTIGU * tab; int taille;int taillemax;} Listet;

Listet listenouv_t();
Listet adjt_t(Listet l,S_LISTE_T_CONTIGU a);
Listet supt_t(Listet l);
Listet adjq_t(Listet l,S_LISTE_T_CONTIGU a);
Listet supq_t(Listet l);
Listet remplacerIndice_t(Listet l,S_LISTE_T_CONTIGU a,int indice);
S_LISTE_T_CONTIGU ieme_t(Listet l,int i);
S_LISTE_T_CONTIGU tete_t(Listet l);
S_LISTE_T_CONTIGU dernier_t(Listet l);
int estvide_t(Listet l);
int tailleliste_t(Listet l);
Listet inserer_t(Listet l,S_LISTE_T_CONTIGU a,int indice);
Listet supprIndice_t(Listet l,int indice);
Listet supprVal_t(Listet l,S_LISTE_T_CONTIGU a);
int indice_t(Listet l,S_LISTE_T_CONTIGU a);
int estdans_t(Listet l,S_LISTE_T_CONTIGU a);
void freeListe_t(Listet l);



#endif

