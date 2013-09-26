/** \file
 *  Source : Fonction de calcul de déterminant/système linéaire
 **/

#include "ALineA-TP2.h"

Matrix extraction(Matrix m,Matrix mtmp,int i,int j)
{
	int k,l;
	for(k=0;k<i;k++)
	{
		for(l=0;l<j;l++) setElt(mtmp,k,l,getElt(m,k,l));
	}
	
	for(k=i+1;k<m->nb_rows;k++)
	{
		for(l=0;l<j;l++) setElt(mtmp,k-1,l,getElt(m,k,l));
	}
	
	for(k=0;k<i;k++)
	{
		for(l=j+1;l<m->nb_columns;l++) setElt(mtmp,k,l-1,getElt(m,k,l));
	}
	
	for(k=i+1;k<m->nb_rows;k++)
	{
		for(l=j+1;l<m->nb_columns;l++) setElt(mtmp,k-1,l-1,getElt(m,k,l));
	}
	return mtmp;
}

Matrix switchLineMAtrix(Matrix m,int i,int j)
{
	E tmp;
	int k=0;
	for(k=0;k<m->nb_columns;k++)
	{
		tmp=getElt(m,i,k);
		setElt(m,i,k,getElt(m,j,k));
		setElt(m,j,k,tmp);
	}
	return m;
}


E m_determinant_rec(Matrix m)
{
	if(m->nb_rows != m->nb_columns)
	{
		fprintf(stderr,"Matrice non carré");
		exit(1);
	}
	if(m->nb_rows == 1) return getElt(m,0,0);
	else
	{
		Matrix mtmp=newMatrix(m->nb_rows-1,m->nb_columns-1);
		int i=0,c=1;
		E det=0;
		E aij=0;
		for(i=0;i<m->nb_rows;i++)
		{
			aij=getElt(m,i,0);
			if(aij !=0)
			{
				mtmp=extraction(m,mtmp,i,0);
				det+=aij*c*m_determinant_rec(mtmp);
			}
			c=-c;
		}
		deleteMatrix(mtmp);
		return det;
	}
			
}


int pivotPartiel(Matrix m,int i)
{
	int j,k=i;
	for(j=i;j<m->nb_rows;j++)
	{
		if(abs(getElt(m,j,i))>abs(getElt(m,k,i))) k=j;
	}
	return k;
}


E triangulaire_det(Matrix m)
{
	int i,j,k,c=1;
	for(j=0;j<m->nb_columns-1;j++)
	{
		k=pivotPartiel(m,j);
		if(getElt(m,k,j)==0) return 0; //0 sur la diagonale
		if(k!=j)
		{
			m=switchLineMAtrix(m,k,j);//Echange de ligne avec le pivot
			c=-c;
		}
		for(i=j+1;i<m->nb_rows;i++)
		{
			linearComb(m,j,i,-(E)getElt(m,i,j)/(E)(getElt(m,j,j)),1.);//Fait apparaitre les 0 en dessus du pivot
		}
	}
	return c;
}


E m_determinant_triangle(Matrix m)
{
	Matrix mtmp=copieMatrix(m);
	E c=triangulaire_det(mtmp);//On triangularise la matrice
	int i;
	if(c!=0)
	{
		for(i=0;i<mtmp->nb_rows;i++) c*=getElt(mtmp,i,i);//On multplie ensemble les éléments de la diagonale
	}
	deleteMatrix(mtmp);
	return c;
}


E triangulaire_gauss(Matrix a,Matrix b)
{
	int i,j,k;
	E tmp;
	for(j=0;j<a->nb_columns-1;j++)
	{
		k=pivotPartiel(a,j);
		if(getElt(a,k,j)==0) return 0; //0 sur la diagonale
		if(k!=j)
		{
			a=switchLineMAtrix(a,k,j);//echange de ligne avec le pivot de A
			b=switchLineMAtrix(b,k,j);//echange de la meme ligne de b
		}
		for(i=j+1;i<a->nb_rows;i++)
		{
			tmp=-getElt(a,i,j)/(getElt(a,j,j));
			linearComb(a,j,i,tmp,1.);//modification sur A
			linearComb(b,j,i,tmp,1.);//modification sur b
		}
	}
	return 1;
}

Matrix remontee(Matrix a,Matrix b)
{
	int i,j;
	Matrix x=newMatrix(b->nb_rows,1);
	for(i=a->nb_rows-1;i>=0;i--)
	{
		setElt(x,i,0,getElt(b,i,0));
		for(j=i+1;j<a->nb_rows;j++) setElt(x,i,0,getElt(x,i,0) - getElt(a,i,j)*getElt(x,j,0));
		setElt(x,i,0,getElt(x,i,0)/getElt(a,i,i));
	}
	return x;
}

Matrix m_gauss(Matrix a,Matrix b)
{
	E c=triangulaire_gauss(a,b);
	Matrix x=NULL;
	if(c!=0) x=remontee(a,b);
	return x;
}
