#include "arbre_generaux.h"


Liste desg(Arbin a,Liste p)
{
	Arbin tmp=a;	
	while(tmp!=NULL)
	{
		p=adjt(p,tmp);
		tmp=ag(tmp);
	}
	return p;
}	

Arbin ge(S x)
{
	return e(NULL,x,NULL);
}

Arbin i(Arbin a,Arbin b,int k)
{
	if(k==1)
	{
		b->d=a->g;
		a->g=b;
	}
	else
	{
		Arbin tmp=a->g;
		k--;
		while(k>1 && tmp->d!=NULL)
		{
			tmp=tmp->d;
			k--;
		}
		b->d=tmp->d;
		tmp->d=b;
	}
	return a;
}

Arbin fils(Arbin a,int k)
{	
	Arbin tmp=ag(a);
	while(k>1)
	{
		tmp=ad(tmp);
		k--;
	}
	return tmp;
}

int ef(Arbin a)
{
	return (ag(a)==NULL);
}

S racine(Arbin a)
{
	return a->v;
}

int nb_fils(Arbin a)
{
	int k=0;
	Arbin tmp=ag(a);
	while(tmp != NULL)
	{
		k++;
		tmp=ad(tmp);
	}
	return k;
}

int nb_noeud(Arbin a)
{
	int i=0;
	Liste l=listenouv();
	l=desg(a,l);
	Arbin tmp;
	while(tailleliste(l) > 0)
	{
		i++;
		tmp=tete(l);
		l=supt(l);
		desg(tmp,l);
	}
	freeListe(l);
	return i;
}

int max(int a,int b)
{
	return (a < b)? b :a;
}

int h(Arbin a)
{
	Liste l=listenouv();
	int max=0;
	l=desg(a,l);
	Arbin tmp;
	max=tailleliste(l);
	while(tailleliste(l) > 0)
	{
		tmp=tete(l);
		l=supt(l);
		desg(ad(tmp),l);
		if(tailleliste(l)>max) max=tailleliste(l);
	}
	return max-1;
}
