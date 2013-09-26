#include "liste_contigue_t.h"


Listet listenouv_t()
{
	Listet l;
	l.taille=0;
	l.taillemax=TAILLE_LISTE;
	l.tab=(S_LISTE_T_CONTIGU*)malloc(TAILLE_LISTE*sizeof(S_LISTE_T_CONTIGU));
	return l;
}

Listet adjt_t(Listet l,S_LISTE_T_CONTIGU a)
{
	if(l.taille==l.taillemax)
	{
		l.tab=(S_LISTE_T_CONTIGU*)realloc(l.tab,(l.taillemax+TAILLE_LISTE)*sizeof(S_LISTE_T_CONTIGU));
		l.taillemax+=TAILLE_LISTE;
	}
	l.tab[l.taille]=a;
	l.taille++;
	return l;
}

Listet supt_t(Listet l)
{
	if(l.taille>0)
	{
		l.taille--;
		if( (l.taille+(2*TAILLE_LISTE)) < l.taillemax )
		{
			l.tab=(S_LISTE_T_CONTIGU*)realloc(l.tab,(l.taillemax-TAILLE_LISTE)*sizeof(S_LISTE_T_CONTIGU));
			l.taillemax-=TAILLE_LISTE;
		}
	}
	return l;
}

Listet adjq_t(Listet l,S_LISTE_T_CONTIGU a)
{
	int i=0;
	for(i=l.taille ; i>0 ; i--) l.tab[i]=l.tab[i-1];
	l.tab[0]=a;
	l.taille++;
	return l;
}

Listet supq_t(Listet l)
{
	if(l.taille>0)
	{
		int i=0;
		for(i=0;i<l.taille-1;i++) l.tab[i]=l.tab[i+1];
		l.taille--;
		}
	return l;
}
Listet remplacerIndice_t(Listet l,S_LISTE_T_CONTIGU a,int indice)
{
	if(indice<l.taille && indice>-1) l.tab[l.taille-indice-1]=a;
	return l;
}

S_LISTE_T_CONTIGU tete_t(Listet l)
{
	return l.tab[l.taille-1];
}

S_LISTE_T_CONTIGU ieme_t(Listet l,int i)
{
    if(i >= l.taille)i=l.taille -1;
    else if(i < 0)i=0;
    return l.tab[i];
}

S_LISTE_T_CONTIGU dernier_t(Listet l)
{
	return l.tab[0];
}

int estvide_t(Listet l)
{
	return (l.taille>0);
}

int tailleliste_t(Listet l)
{
	return l.taille;
}


Listet inserer_t(Listet l,S_LISTE_T_CONTIGU a,int indice)
{
	int i=0;
	for(i=0;i<indice;i++) l.tab[l.taille-i]=l.tab[l.taille-i-1];
	l.tab[l.taille-indice]=a;
	l.taille++;
	return l;
}

Listet supprIndice_t(Listet l,int indice)
{
	if((indice<l.taille) && (indice>=0))
	{
		int i=0;
		for(i=l.taille-indice;i<l.taille;i++) l.tab[i]=l.tab[i+1];
		l.taille--;
	}
	return l;
}

int indice_t(Listet l,S_LISTE_T_CONTIGU a)
{
	int i=0,indice=-1;
	for(i=l.taille-1;(i>=0)&&(indice==-1);i--) if(l.tab[i]==a) indice=i;
	return l.taille-indice;
}
Listet supprVal_t(Listet l,S_LISTE_T_CONTIGU a)
{
	return supprIndice_t(l,indice_t(l,a));
}




int estdans_t(Listet l,S_LISTE_T_CONTIGU a)
{
	return (indice_t(l,a) != -1);
}

void freeListe_t(Listet l)
{
	free(l.tab);
	l.taille=0;
}
