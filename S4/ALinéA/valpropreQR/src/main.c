#include <stdio.h>
#include <stdlib.h>

#include "ALineA-TP1.h"
#include "valeur_propre.h"


int main(int argc, char *argv[])
{
	Matrix A=NULL;
	Matrix v=NULL;
	A=saisirMatrix();

	displayMatrix(A);

	int i=valeurPropre(A,&v);

	printf("Valeurs propres (avec %d itérations) :\n",i);

	displayMatrix(v);

	deleteMatrix(A);
	deleteMatrix(v);

	return 0;
}
