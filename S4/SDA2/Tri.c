#include <stdio.h>
#include <stdlib.h>

typedef int S;
S * trishake(S * tab,int n)
{
	int i=0,j=n,k=0,continu=1;
	S tmp=0;
	while(i != j)
	{

		for(k=i;(k<j-1) && continu;k++)
		{
			continu=0;
			if(tab[k]>tab[k+1])
			{
				tmp=tab[k];
				tab[k]=tab[k+1];
				tab[k+1]=tmp;
				continu=1;
			}
		}

		j--;
		for(k=j;k>i;k--)
		{
			if(tab[k]<tab[k-1])
			{
				tmp=tab[k];
				tab[k]=tab[k-1];
				tab[k-1]=tmp;
				continu=1;
			}
		}
		i++;
	}

	return tab;
}

S * tribulle(S * tab,int n)
{
	int i=0,j=0;
	S tmp=0;
	int continu=1;

		for(j=0;(j<n) && (continu);j++)
		{
			continu=0;
			for(i=0;i<n-j-1;i++)
			{
				if(tab[i]>tab[i+1])
				{
					tmp=tab[i];
					tab[i]=tab[i+1];
					tab[i+1]=tmp;
					continu=1;
				}
			}
		}
	return tab;
}

S * triCourse(S * tab,int n)
{
	S * tmp=NULL;
	tmp=malloc(n*sizeof(S));
	int i=0,j=0;
	int indice=-1;
	
	for(i=0;i<n;i++)
	{
		/* Premier essai
		indice=0;
		for(j=0;j<i & (indice==-1);j++) if(tab[i]>tmp[j]) indice=j; 
		for(j=i;j>indice;j--) tmp[j]=tmp[j-1];
		tmp[indice]=tab[i];
		indice=-1;
		*/
	
		indice=0
		for(j=i;j>indice;j--)
		{
			if(tab[i]<tmp[j-1]) tmp[j]=tmp[j-1];
			else indice=j; 
		}
		tmp[indice]=tab[i];
	}
	
	for(i=0;i<n;i++) tab[i]=tmp[i];
	free(tmp);
	return tab;
}
	
			
int dich(S * tab,int n,int a,int b,S x)
{
	int m;
	if(a==b) return a;
	else
	{
		m=(a+b)/2;
		if(tab[m]<x) return dich(tab,n,m+1,b,x);
		else return dich(tab,n,a,m,x);
	}
}

S * tridicho(S * tab,int n)
{
	int i,j,k;
	S x;
	for(i=1;i<n;i++)
	{
		x=t[i];
		j=dich(tab,n,0,i,x); //position
		for(k=i;k>j;k--) tab[k]=t[k-1];
		tab[j]=x;
	}
	return tab;
}
