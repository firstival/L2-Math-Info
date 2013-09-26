#ifndef __EXO2_H
#define __EXO2_H

#include <stdio.h>
#include <stdlib.h>

#include "arbre_binaire.h"
#include "liste_contigue_a.h"
#include "liste_contigue.h"


int imin(Liste l,int j,int k);
Arbin la(Liste l);
Arbin la_aux(Liste l,int i,int j);
Liste al(Arbin a);
Arbin union0(Arbin a1,Arbin a2);
Arbin union1(Arbin a1,Arbin a2);
Arbin om(Arbin a);
Arbin ins(Arbin a,ARBRE_BIN_S x);


#endif

