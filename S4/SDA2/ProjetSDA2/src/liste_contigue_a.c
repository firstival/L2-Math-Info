#include "liste_contigue_a.h"


Listea listenouv_a()
{
	Listea l;
	l.taille=0;
	l.taillemax=TAILLE_LISTE;
	l.tab=(S_LISTE_A_CONTIGU*)malloc(TAILLE_LISTE*sizeof(S_LISTE_A_CONTIGU));
	return l;
}

Listea adjt_a(Listea l,S_LISTE_A_CONTIGU a)
{
	if(l.taille==l.taillemax)
	{
		l.tab=(S_LISTE_A_CONTIGU*)realloc(l.tab,(l.taillemax+TAILLE_LISTE)*sizeof(S_LISTE_A_CONTIGU));
		l.taillemax+=TAILLE_LISTE;
	}
	l.tab[l.taille]=a;
	l.taille++;
	return l;
}

Listea supt_a(Listea l)
{
	if(l.taille>0)
	{
		l.taille--;
		if( (l.taille+(2*TAILLE_LISTE)) < l.taillemax )
		{
			l.tab=(S_LISTE_A_CONTIGU*)realloc(l.tab,(l.taillemax-TAILLE_LISTE)*sizeof(S_LISTE_A_CONTIGU));
			l.taillemax-=TAILLE_LISTE;
		}
	}
	return l;
}

Listea adjq_a(Listea l,S_LISTE_A_CONTIGU a)
{
	int i=0;
	for(i=l.taille ; i>0 ; i--) l.tab[i]=l.tab[i-1];
	l.tab[0]=a;
	l.taille++;
	return l;
}

Listea supq_a(Listea l)
{
	if(l.taille>0)
	{
		int i=0;
		for(i=0;i<l.taille-1;i++) l.tab[i]=l.tab[i+1];
		l.taille--;
		}
	return l;
}
Listea remplacerIndice_a(Listea l,S_LISTE_A_CONTIGU a,int indice)
{
	if(indice<l.taille && indice>-1) l.tab[l.taille-indice-1]=a;
	return l;
}

S_LISTE_A_CONTIGU tete_a(Listea l)
{
	return l.tab[l.taille-1];
}

S_LISTE_A_CONTIGU ieme_a(Listea l,int i)
{
    if(i >= l.taille)i=l.taille -1;
    else if(i < 0)i=0;
    return l.tab[i];
}

S_LISTE_A_CONTIGU dernier_a(Listea l)
{
	return l.tab[0];
}

int estvide_a(Listea l)
{
	return (l.taille>0);
}

int tailleliste_a(Listea l)
{
	return l.taille;
}

Listea inserer_a(Listea l,S_LISTE_A_CONTIGU a,int indice)
{
	int i=0;
	for(i=0;i<indice;i++) l.tab[l.taille-i]=l.tab[l.taille-i-1];
	l.tab[l.taille-indice]=a;
	l.taille++;
	return l;
}

Listea supprIndice_a(Listea l,int indice)
{
	if((indice<l.taille) && (indice>=0))
	{
		int i=0;
		for(i=l.taille-indice;i<l.taille;i++) l.tab[i]=l.tab[i+1];
		l.taille--;
	}
	return l;
}

int indice_a(Listea l,S_LISTE_A_CONTIGU a)
{
	int i=0,indice=-1;
	for(i=l.taille-1;(i>=0)&&(indice==-1);i--) if(l.tab[i]==a) indice=i;
	return l.taille-indice;
}
Listea supprVal_a(Listea l,S_LISTE_A_CONTIGU a)
{
	return supprIndice_a(l,indice_a(l,a));
}




int estdans_a(Listea l,S_LISTE_A_CONTIGU a)
{
	return (indice_a(l,a) != -1);
}

void freeListe_a(Listea l)
{
	free(l.tab);
	l.taille=0;
}
