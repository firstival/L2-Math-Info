/** \file
 * Source : Liste chainée simple
 **/

#include "liste_chaine_simple.h"

Liste listenouv()
{
	Liste l=NULL;
	l=(Liste)malloc(sizeof(StrListe));
	l->taille=0;
	l->t=NULL;
	l->q=NULL;
	return l;
}

Liste adjt(Liste l,S_LISTE_CHAINE_SIMPLE a)
{
	ListeElem new=NULL;
	new=(ListeElem)malloc(sizeof(StrListeElem));

	new->val=a;
	new->suiv=l->t;

	l->t=new;
	if(l->taille<1) l->q=new;
	l->taille++;
	return l;
}

Liste supt(Liste l)
{
	if(l->t != NULL)
	{
		ListeElem tmp=l->t;
		l->t=l->t->suiv;
		free(tmp);
		l->taille--;
	}
	return l;
}



Liste adjq(Liste l,S_LISTE_CHAINE_SIMPLE a)
{
	ListeElem new=NULL;
	new=(ListeElem)malloc(sizeof(StrListeElem));

	new->val=a;
	new->suiv=NULL;

	if(l->taille<1) l->t=new;

	if(l->q != NULL) l->q->suiv=new;
	l->q=new;
	l->taille++;

	return l;
}

Liste supq(Liste l)
{
	if(l->taille >0)
	{
		if(l->taille==1) l=supt(l);
		else
		{
			int i=0;
			ListeElem tmp=l->t;
			for(i=0;i < l->taille-2;i++) tmp=tmp->suiv;
			free(l->q);
			l->q=tmp;
			tmp->suiv=NULL;
		}
	}
	return l;
}

Liste remplacer(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice)
{
	int i=0;
	ListeElem tmp=l->t;

	for(i=0;i<indice;i++) tmp=tmp->suiv;
	tmp->val=a;
	return l;
}

S_LISTE_CHAINE_SIMPLE tete(Liste l)
{
	return l->t->val;
}

S_LISTE_CHAINE_SIMPLE dernier(Liste l)
{
	return l->q->val;
}

int estvide(Liste l)
{
	return (l->taille > 0);
}

int tailleliste(Liste l)
{
	return l->taille;
}

void afficherliste(Liste l)
{
	int i=0;
	ListeElem tmp=l->t;
	for(i=0;i<l->taille-1;i++)
	{
		printf("%d | ", tmp->val.pid);
		tmp=tmp->suiv;
	}
	if(l->taille > 0) printf("%d",l->q->val.pid);
}

Liste inserer(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice)
{
	if(indice<0) l=adjt(l,a);
	else
	{
		if(indice>l->taille) indice=l->taille;

		ListeElem tmp=l->t,new=NULL;
		int i=0;
		for(i=0;i<indice;i++)tmp=tmp->suiv;

		new=(ListeElem)malloc(sizeof(StrListeElem));
		new->val=a;
		new->suiv=tmp->suiv;
		tmp->suiv=new;
		l->taille++;
	}
	return l;
}


Liste supprIndice(Liste l,int indice)
{
	if((indice < l->taille) && (indice >=0))
	{
		if(indice==0) l=supt(l);
		else
		{
			int i=0;
			ListeElem tmp=l->t,tmpfree=NULL;
			for(i=0;i<indice-1;i++)	tmp=tmp->suiv;
			tmpfree=tmp->suiv;
			tmp->suiv=(tmp->suiv)->suiv;
			free(tmpfree);
			l->taille--;
		}
	}

	return l;
}


ListeElem adresseIeme(Liste l,int i)
{
	ListeElem tmp=l->t;
	while((l!=NULL)&&(i>0))
	{
		tmp=tmp->suiv;
		i--;
	}
	return tmp;
}

void freeListe(Liste l)
{
	ListeElem tmp=NULL;
	while(l->t != NULL)
	{
		tmp=l->t;
		l->t=l->t->suiv;
		free(tmp);
	}
	free(l);
}
