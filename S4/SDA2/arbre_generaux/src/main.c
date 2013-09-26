#include <stdio.h>
#include <stdlib.h>
#include "arbre_generaux.h"
#include "arbre_binaire.h"


int main(int argc, char *argv[])
{
	Arbin a=i( i(ge(1),ge(2),1)  ,  i(ge(3),ge(4),1)  ,2);
	afficherArbre(a);
	Arbin b=fils(a,2);
	afficherArbre(b);
	printf("1er fils de (1) est une feuilles? %d , et le 2eme fils? %d\n",ef(fils(a,1)),ef(fils(a,2)));
	printf("racine du 2eme fils :%d\n", racine(fils(a,2)));
	printf("nombre de fils :%d\n",nb_fils(a));
	printf("nombre de noeud : %d\n",nb_noeud(a));//
	printf("hauteur de a : %d\n", h(a));//
	return 0;
}
