#include "ALineA-TP2.h"

int main()
{
	srand(time(NULL));
	Matrix a=newMatrix(2,2);
	a=randomMatrix(a);
	printf("Matrice 2x2 :\n");
	displayMatrix(a);
	E c=m_determinant_triangle(a);
	printf("Calcul du determinant avec triangularisation : %.5f\n", c);
	c=m_determinant_rec(a);
	printf("Calcul du determinant recursivement : %.5f\n\n\n", c);
	deleteMatrix(a);
	
	a=newMatrix(3,3);
	a=randomMatrix(a);
	printf("Matrice 3x3 :\n");
	displayMatrix(a);
	c=m_determinant_triangle(a);
	printf("Calcul du determinant avec triangularisation : %.5f\n", c);
	c=m_determinant_rec(a);
	printf("Calcul du determinant recursivement : %.5f\n\n\n", c);
	
	printf("Demonstration des fonctions de resolutions de systemes AX=B \n");
	setElt(a,0,0,1);
	setElt(a,0,1,-1);
	setElt(a,0,2,2);
	setElt(a,1,0,3);
	setElt(a,1,1,2);
	setElt(a,1,2,1);
	setElt(a,2,0,2);
	setElt(a,2,1,-3);
	setElt(a,2,2,-2);
	Matrix b=newMatrix(3,1);
	setElt(b,0,0,5);
	setElt(b,1,0,10);
	setElt(b,2,0,-10);
	printf("A = \n");
	displayMatrix(a);
	printf("B = \n");
	displayMatrix(b);
	Matrix x=m_gauss(a,b);
	printf("Apres calcul, X = \n");
	displayMatrix(x);
	deleteMatrix(a);
	deleteMatrix(b);
	
	printf("Voulez vous calculer le determinant d'une matrice personnelle? O/N\n");
	char ch=getchar();
	if(ch=='o' || ch=='O')
	{
		a=saisirMatrix();
		displayMatrix(a);
		c=m_determinant_triangle(a);
		printf("Calcul du determinant avec triangularisation : %.5f\n", c);
		c=m_determinant_rec(a);
		printf("Calcul du determinant recursivement : %.5f\n\n\n", c);
		deleteMatrix(a);
	}
	
	return 0;
}
