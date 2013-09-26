#ifndef __LISTE_A_CONTIGU_H
#define __LISTE_A_CONTIGU_H

#include <stdio.h>
#include <stdlib.h>
#include "sorte_arbre.h"

#define TAILLE_LISTE 50

typedef Arbin S_LISTE_A_CONTIGU;

typedef struct { S_LISTE_A_CONTIGU * tab; int taille;int taillemax;} Listea;

Listea listenouv_a();
Listea adjt_a(Listea l,S_LISTE_A_CONTIGU a);
Listea supt_a(Listea l);
Listea adjq_a(Listea l,S_LISTE_A_CONTIGU a);
Listea supq_a(Listea l);
Listea remplacerIndice_a(Listea l,S_LISTE_A_CONTIGU a,int indice);
S_LISTE_A_CONTIGU ieme_a(Listea l,int i);
S_LISTE_A_CONTIGU tete_a(Listea l);
S_LISTE_A_CONTIGU dernier_a(Listea l);
int estvide_a(Listea l);
int tailleliste_a(Listea l);
Listea inserer_a(Listea l,S_LISTE_A_CONTIGU a,int indice);
Listea supprIndice_a(Listea l,int indice);
Listea supprVal_a(Listea l,S_LISTE_A_CONTIGU a);
int indice_a(Listea l,S_LISTE_A_CONTIGU a);
int estdans_a(Listea l,S_LISTE_A_CONTIGU a);
void freeListe_a(Listea l);



#endif

