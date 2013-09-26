#include <stdio.h>
#include <stdlib.h>

#include "ALineA-TP1.h"
#include "valeur_propre.h"
#include <time.h>


int main(int argc, char *argv[])
{
    if(argc<3)
    {
        printf("Usage : %s <taille de la matrice> <filename>\n",argv[0]);
		exit(1);
    }
    srand(time(NULL));
    int taille=atoi(argv[1]);
	Matrix A=newMatrix(taille,taille);
	A=randomMatrix(A);

	valeurPropre_gnuplot(A,argv[2]);

	deleteMatrix(A);

	return 0;
}
