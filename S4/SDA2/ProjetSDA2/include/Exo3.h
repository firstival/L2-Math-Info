#ifndef __EXO3_H
#define __EXO3_H

#include <stdio.h>
#include <stdlib.h>

#include "liste_contigue.h"
#include "liste_contigue_t.h"
#include "sorte_tournoi_position.h"


typedef struct couple {TournoiBinPos a1;TournoiBinPos a2;} CoupleTournoiBinPos;

Listet desd(TournoiBinPos a,Listet p);
TournoiBinPos tournoinouv();
TournoiBinPos e(TournoiBinPos g,int n,S_TOURNOI_POSITION x,TournoiBinPos d);
S_TOURNOI_POSITION r(TournoiBinPos a);
TournoiBinPos ag(TournoiBinPos a);
TournoiBinPos ad(TournoiBinPos a);
int v(TournoiBinPos a);
int nn(TournoiBinPos a);
int hauteur(TournoiBinPos a);
void freeArbre(TournoiBinPos t);


int imin(Liste l,int j,int k);
TournoiBinPos la(Liste l);
TournoiBinPos la_aux(Liste l,int i,int j);
Liste al(TournoiBinPos a);
S_TOURNOI_POSITION el(TournoiBinPos a,int k);
TournoiBinPos union1(TournoiBinPos a1,TournoiBinPos a2);
CoupleTournoiBinPos coup(TournoiBinPos a,int k);
TournoiBinPos ins(TournoiBinPos a,S_TOURNOI_POSITION x, int k);
TournoiBinPos sup(TournoiBinPos a,int k);


#endif

