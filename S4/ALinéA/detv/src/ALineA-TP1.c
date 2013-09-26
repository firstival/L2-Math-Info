/** \file
 * Source : Fonction sur les matrices du TP1
 **/

#include "ALineA-TP1.h"

Matrix newMatrix(int nb_rows,int nb_columns)
{
	Matrix new=NULL;
	new=(Matrix)malloc(sizeof(StrMatrix));
	new->mat=(E*)malloc(sizeof(E)*nb_rows*nb_columns);
	new->nb_rows=nb_rows;
	new->nb_columns=nb_columns;
	
	int i=0;
	for(i=0;i<nb_rows*nb_columns;i++) new->mat[i]=0;
	
	return new;
}

E getElt(Matrix m,int row,int column)
{
	return m->mat[column*(m->nb_rows) + row];
}

void setElt(Matrix m,int row,int column,E val)
{
	m->mat[column*(m->nb_rows) + row]=val;
}

void deleteMatrix(Matrix m)
{
	free(m->mat);
	free(m);
}

int isSquare(Matrix m)
{
	return m->nb_columns==m->nb_rows;
}

int isSymetric(Matrix m)
{
	int i=0,j=0;
	int resultat=0;
	if(isSquare(m))
	{
		resultat=1;
		for(i=0;(i<m->nb_columns)&&resultat;i++)
		{
			for(j=0;(j<=i)&&resultat;i++)
			{
				if(getElt(m,j,i)!=getElt(m,i,j)) resultat=0;
			}
		}
	}
	return resultat;
}

Matrix transpose(Matrix m)
{
	int i=0,j=0;
	
	Matrix new=newMatrix(m->nb_columns,m->nb_rows);
	for(j=0;j<new->nb_columns;j++)
	{
		for(i=0;i<new->nb_rows;i++) setElt(new,i,j,getElt(m,j,i));
	}
	return new;
}

Matrix addition(Matrix m1,Matrix m2)
{
	Matrix m=NULL;
	if((m1->nb_columns==m2->nb_columns)&&(m1->nb_rows==m2->nb_rows))
	{
		int i=0,j=0;
		m=newMatrix(m1->nb_rows,m1->nb_columns);
		for(i=0;i<m1->nb_columns;i++)
		{
			for(j=0;j<m1->nb_rows;j++) setElt(m,j,i,getElt(m1,j,i) + getElt(m2,j,i));
		}
	}
	return m;
}

Matrix multiplication(Matrix m1,Matrix m2)
{
	int i=0,j=0,k=0;
	Matrix m=NULL;
	if(m1->nb_columns == m2->nb_rows)
	{
		m=newMatrix(m1->nb_rows,m2->nb_columns);
		for(i=0;i<m->nb_columns;i++)
		{
			for(j=0;j<m->nb_rows;j++)
			{
				for(k=0;k<m1->nb_columns;k++) setElt(m,j,i,getElt(m,j,i) + (getElt(m1,j,k) * getElt(m2,k,i)) );
			}
		}
	}
	return m;
}

Matrix mult_scalar(E x,Matrix m1)
{
	int i=0,j=0;
	Matrix m=NULL;
	m=newMatrix(m1->nb_rows,m1->nb_columns);
	for(i=0;i<m->nb_rows;i++)
	{
		for(j=0;j<m->nb_columns;j++)
		{
			setElt(m,i,j,getElt(m1,i,j) * x);
		}
	}
	return m;
}

void displayMatrix(Matrix m)
{
	int i=0,j=0;
	for(i=0;i<m->nb_rows;i++)
	{
		for(j=0;j<m->nb_columns;j++)
		{
			printf("%.3f\t",getElt(m,i,j));
		}
		printf("\n");
	}
	printf("\n");
}

Matrix linearComb(Matrix m,int line1,int line2,E scal1,E scal2)
{
	int i=0;
	for(i=0;i<m->nb_columns;i++) setElt(m,line2,i, (getElt(m,line1,i) * scal1) + (getElt(m,line2,i) * scal2));
	return m;
}

Matrix saisirMatrix()
{
	int nb_columns,nb_rows,i,j;
	float k;
	printf("Nombre de ligne :");
	scanf(" %d",&nb_rows);
	printf("Nombre de colonnes :");
	scanf(" %d",&nb_columns);
	
	Matrix m=newMatrix(nb_rows,nb_columns);
	
	for(j=0;j<nb_rows;j++)
	{
		for(i=0;i<nb_columns;i++)
		{
			scanf(" %f",&k);
			setElt(m,j,i,k);
		}
	}
	return m;
}

Matrix randomMatrix(Matrix m)
{
	int i=0,j=0;
	for(i=0;i<m->nb_rows;i++)
	{
		for(j=0;j<m->nb_columns;j++)
		{
			setElt(m,i,j,rand()%RANDOM_NUMBER);
		}
	}
	return m;
}

Matrix copieMatrix(Matrix m)
{
	Matrix tmp=newMatrix(m->nb_rows,m->nb_columns);
	int i,j;
	for(i=0;i<m->nb_rows;i++)
	{
		for(j=0;j<m->nb_columns;j++) setElt(tmp,i,j,getElt(m,i,j));
	}
	
	return tmp;	
}
