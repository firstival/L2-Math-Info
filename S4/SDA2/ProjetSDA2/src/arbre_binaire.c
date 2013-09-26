#include "arbre_binaire.h"

int pow2(int n)
{
	int a=1;
	while(n>0)
	{
		a*=2;
		n--;
	}
	return a;
}

Listea desd(Arbin a,Listea p)
{
	Arbin tmp=a;
	while(tmp!=NULL)
	{
		p=adjt_a(p,tmp);
		tmp=ad(tmp);
	}
	return p;
}

Arbin newArbin()
{
	return NULL;
}


Arbin e(Arbin a,ARBRE_BIN_S v,Arbin b)
{
	Arbin r=NULL;
	r=(Arbin)malloc(sizeof(StrArbin));
	r->v=v;
	r->g=a;
	r->d=b;
	return r;
}


ARBRE_BIN_S rac(Arbin a)
{
	return a->v;
}


Arbin ag(Arbin a)
{
	if(a==NULL) return NULL;
	else return a->g;
}


Arbin ad(Arbin a)
{
	if(a==NULL) return NULL;
	return a->d;
}


int vide(Arbin a)
{
	return (a!=NULL);
}


int nn(Arbin a)
{
	int total=0,i=0,indice=0;
	Listea l=listenouv_a();
	l=adjt_a(l,a);
	while(l.taille !=total)
	{
		total=l.taille;
		for(i=indice;i<total;i++)
		{
			if(l.tab[i]->g!=NULL) l=adjt_a(l,l.tab[i]->g);
			if(l.tab[i]->d!=NULL) l=adjt_a(l,l.tab[i]->d);
		}
		indice=total;
	}
	freeListe_a(l);
	return total;
}


int nf(Arbin a)
{
	int i=0,indice=0,k=0,nb_feuille=0;
	Listea l=listenouv_a();
	l=adjt_a(l,a);
	while(l.taille !=k)
	{
		k=l.taille;
		for(i=indice;i<k;i++)
		{
			if((l.tab[i]->g==NULL)&&(l.tab[i]->d==NULL)) nb_feuille++;
			else
			{
				if(l.tab[i]->g!=NULL) l=adjt_a(l,l.tab[i]->g);
				if(l.tab[i]->d!=NULL) l=adjt_a(l,l.tab[i]->d);
			}
		}
		indice=k;
	}
	freeListe_a(l);
	return nb_feuille;
}


int ni(Arbin a)
{
	int total=0,i=0,indice=0,k=0,bit=0;
	Listea l=listenouv_a();
	l=adjt_a(l,a);
	while(l.taille !=total)
	{
		total=l.taille;
		for(i=indice;i<total;i++)
		{
			bit=0;
			if(l.tab[i]->g!=NULL)
			{
				l=adjt_a(l,l.tab[i]->g);
				bit=1;
			}
			if(l.tab[i]->d!=NULL)
			{
				l=adjt_a(l,l.tab[i]->d);
				bit=1;
			}
			if(bit) k++;
		}
		indice=total;
	}
	freeListe_a(l);
	return k;
}


int hauteur(Arbin a)
{
	int total=0,i=0,indice=0,k=0,bit=0;
	Listea l=listenouv_a();
	l=adjt_a(l,a);
	while(l.taille !=total)
	{
		total=l.taille;
		for(i=indice;i<total;i++)
		{
			if(l.tab[i]->g!=NULL)
			{
				l=adjt_a(l,l.tab[i]->g);
				bit=1;
			}
			if(l.tab[i]->d!=NULL)
			{
				l=adjt_a(l,l.tab[i]->d);
				bit=1;
			}

		}
		if(bit)
		{
			k++;
			bit=0;
		}
		indice=total;
	}
	freeListe_a(l);
	return k;
}


Arbin extr_g(Arbin a)
{
	Arbin tmp=a;
	while(tmp->g != NULL) tmp=tmp->g;
	return tmp;
}


Arbin extr_d(Arbin a)
{
	Arbin tmp=a;
	while(tmp->d != NULL) tmp=tmp->d;
	return tmp;
}


int f(Arbin a)
{
	return (a->g==NULL && a->d==NULL);
}


int appartient(Arbin a,ARBRE_BIN_S v)
{
	int total=0,i=0,indice=0,stop=0;
	Listea l=listenouv_a();
	l=adjt_a(l,a);
	while(l.taille !=total && !stop)
	{
		total=l.taille;
		for(i=indice;i<total && !stop;i++)
		{
			if(l.tab[i]->v==v)stop=1;
			else
			{
				if(l.tab[i]->g!=NULL) l=adjt_a(l,l.tab[i]->g);
				if(l.tab[i]->d!=NULL) l=adjt_a(l,l.tab[i]->d);
			}
		}
		indice=total;
	}
	freeListe_a(l);
	return stop;
}


int hauteur_noeud(Arbin a,ARBRE_BIN_S v)
{
	int total=0,i=0,indice=0,k=0,bit=0,stop=0;
	Listea l=listenouv_a();
	l=adjt_a(l,a);
	while(l.taille !=total && !stop)
	{
		total=l.taille;
		for(i=indice;i<total && !stop;i++)
		{
			if(l.tab[i]->v==v) stop=1;
			else
			{
				if(l.tab[i]->g!=NULL)
				{
					l=adjt_a(l,l.tab[i]->g);
					bit=1;
				}
				if(l.tab[i]->d!=NULL)
				{
					l=adjt_a(l,l.tab[i]->d);
					bit=1;
				}
			}
		}
		if(bit)
		{
			k++;
			bit=0;
		}
		indice=total;
	}
	if(!stop)k=-1;
	freeListe_a(l);
	return k;
}


Listea bordgauche(Arbin a)
{
	Listea l=listenouv_a();
	Arbin tmp=a;
	l=adjt_a(l,a);
	while(tmp->g != NULL)
	{
		tmp=tmp->g;
		l=adjt_a(l,tmp);
	}
	return l;
}


Listea borddroit(Arbin a)
{
	Listea l=listenouv_a();
	Arbin tmp=a;
	l=adjt_a(l,a);
	while(tmp->d != NULL)
	{
		tmp=tmp->d;
		l=adjt_a(l,tmp);
	}
	return l;
}


int locc(Arbin a)
{
	int total=0,i=0,indice=0,stop=1;
	Listea l=listenouv_a();
	l=adjt_a(l,a);
	while(l.taille !=total && stop)
	{
		total=l.taille;
		for(i=indice;i<total && stop;i++)
		{
			if((l.tab[i]->g==NULL) ^ (l.tab[i]->d==NULL))stop=0;
			if(l.tab[i]->g!=NULL) l=adjt_a(l,l.tab[i]->g);
			if(l.tab[i]->d!=NULL) l=adjt_a(l,l.tab[i]->d);
		}
		indice=total;
	}
	freeListe_a(l);
	return stop;
}
// peut etre afficher que qques espaces
void printTab(int k)
{
	int i=0;
	for(i=0;i<k;i++) printf(" ");
}

void afficherValeurArbre(Arbin a)
{
	printf("%d",rac(a));
}

void afficherArbre(Arbin a)
{
	int h=hauteur(a);
	int n=pow2(h+1)-1;
	int k=1;
	int z=n;
	Arbin * t=(Arbin *)malloc(n*sizeof(Arbin));
	int i=0,j=1;
	t[0]=a;
	for(i=0;j<n;i++)
	{
		if(t[i]!=NULL)
		{
			
			t[j]=ag(t[i]);
			t[j+1]=ad(t[i]);
		}
		else
		{
			t[j]=NULL;
			t[j+1]=NULL;
		}
		
		j+=2;
	}
	i=0;
	while(i<n)
	{
		printTab(z);
		for(i=i;i<k;i++)
		{
			if(t[i]==NULL) printf(" ");
			else afficherValeurArbre(t[i]);
			printTab(z*2+1);
		}
		h--;
		k=k*2+1;
		z/=2;
		printf("\n");
	}
	printf("\n");
	free(t);
}

Arbin copieArbre(Arbin a)
{
    if(a==NULL) return NULL;
    else return e(copieArbre(a->g),a->v,copieArbre(a->d));
}
void freeArbre(Arbin a)
{
    if(a!=NULL)
    {
        freeArbre(a->g);
        freeArbre(a->d);
        free(a);
    }
}
