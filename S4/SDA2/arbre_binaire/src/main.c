#include <stdio.h>
#include <stdlib.h>
#include "arbre_binaire.h"
//#include "liste_contigue.h"


int main(int argc, char *argv[])
{
	
	Arbin a=e(e(e(e(NULL,4,NULL),2,e(NULL,5,NULL)),1,e(NULL,3,NULL)),0,e(e(e(NULL,9,NULL),7,e(NULL,10,NULL)),6,e(NULL,8,NULL)));
	afficherArbre(a);
	printf("\nnn :%d",nn(a));
	printf("\nnf :%d",nf(a));
	printf("\nni :%d",ni(a));
	printf("\nh :%d",hauteur(a));
	printf("\nextreme gauche :%d",rac(extr_g(a)));
	printf("\nextreme droit :%d",rac(extr_d(a)));
	printf("\n3 appartient ? : %d",appartient(a,3));
	printf("\nhauteur noeud 4 :%d\n",hauteur_noeud(a,4));
	
	return 0;
}
