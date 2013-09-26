#include "liste_contigue.h"


Liste listenouv()
{
	Liste l=(Liste)malloc(sizeof(StrListe));
	l->taille=0;
	l->taillemax=TAILLE_LISTE;
	l->tab=(S_LISTE_CONTIGU*)malloc(TAILLE_LISTE*sizeof(S_LISTE_CONTIGU));
	return l;
}

Liste adjt(Liste l,S_LISTE_CONTIGU a)
{
	if(l->taille==l->taillemax)
	{
		l->tab=(S_LISTE_CONTIGU*)realloc(l->tab,(l->taillemax+TAILLE_LISTE)*sizeof(S_LISTE_CONTIGU));
		l->taillemax+=TAILLE_LISTE;
	}
	l->tab[l->taille]=a;
	l->taille++;
	return l;
}

Liste supt(Liste l)
{
	if(l->taille>0)
	{
		l->taille--;
		if( (l->taille+(2*TAILLE_LISTE)) < l->taillemax )
		{
			l->tab=(S_LISTE_CONTIGU*)realloc(l->tab,(l->taillemax-TAILLE_LISTE)*sizeof(S_LISTE_CONTIGU));
			l->taillemax-=TAILLE_LISTE;
		}
	}
	return l;
}

Liste adjq(Liste l,S_LISTE_CONTIGU a)
{
	int i=0;
	for(i=l->taille ; i>0 ; i--) l->tab[i]=l->tab[i-1];
	l->tab[0]=a;
	l->taille++;
	return l;
}

Liste supq(Liste l)
{
	if(l->taille>0)
	{
		int i=0;
		for(i=0;i<l->taille-1;i++) l->tab[i]=l->tab[i+1];
		l->taille--;
		}
	return l;
}
Liste remplacerIndice(Liste l,S_LISTE_CONTIGU a,int indice)
{
	if(indice<l->taille && indice>-1) l->tab[l->taille-indice-1]=a;
	return l;
}

S_LISTE_CONTIGU ieme(Liste l,int i)
{
	if(i >= l->taille)i=l->taille-1;
    else if(i < 0)i=0;
    return l->tab[l->taille-1-i];
}

S_LISTE_CONTIGU tete(Liste l)
{
	return l->tab[l->taille-1];
}

S_LISTE_CONTIGU dernier(Liste l)
{
	return l->tab[0];
}

int estvide(Liste l)
{
	return (l->taille<1);
}

int tailleliste(Liste l)
{
	return l->taille;
}

void afficherliste(Liste l)
{
	int i=0;
	for(i=0;i<l->taille-1;i++) printf("%d | ",l->tab[l->taille-i-1]);
	if(l->taille > 0) printf("%d",l->tab[0]);
	printf("\n");
}

Liste inserer(Liste l,S_LISTE_CONTIGU a,int indice)
{
	int i=0;
	for(i=0;i<indice;i++) l->tab[l->taille-i]=l->tab[l->taille-i-1];
	l->tab[l->taille-indice]=a;
	l->taille++;
	return l;
}

Liste supprIndice(Liste l,int indice)
{
	if((indice<l->taille) && (indice>=0))
	{
		int i=0;
		for(i=l->taille-indice;i<l->taille;i++) l->tab[i]=l->tab[i+1];
		l->taille--;
	}
	return l;
}

int indice(Liste l,S_LISTE_CONTIGU a)
{
	int i=0,indice=-1;
	for(i=l->taille-1;(i>=0)&&(indice==-1);i--) if(l->tab[i]==a) indice=i;
	return l->taille-indice;
}
Liste supprVal(Liste l,S_LISTE_CONTIGU a)
{
	return supprIndice(l,indice(l,a));
}

Liste concat(Liste l1,Liste l2)
{
    Liste l=listenouv();
    int i=0;
    for(i=0;i<tailleliste(l2);i++) l=adjt(l,l2->tab[i]);
    for(i=0;i<tailleliste(l1);i++) l=adjt(l,l1->tab[i]);
    return l;
}


int estdans(Liste l,S_LISTE_CONTIGU a)
{
	return (indice(l,a) != -1);
}

void freeListe(Liste l)
{
	free(l->tab);
	free(l);
}


Liste randomListe(int n)
{
	int i=0;
	Liste l=listenouv();
	for(i=0;i<n;i++)
	{
		adjt(l,rand() % (LISTE_RAND_MAX-1) + 2);
	}
	return l;
}
