#include "listel_chaine_simple.h"

Listel listenouv_l()
{
	Listel l=NULL;
	l=(Listel)malloc(sizeof(StrListel));
	l->taille=0;
	l->t=NULL;
	l->q=NULL;
	return l;
}

Listel adjt_l(Listel l,S_LISTEL_CHAINE_SIMPLE a)
{
	ListelElem new=NULL;
	new=(ListelElem)malloc(sizeof(StrListelElem));

	new->val=a;
	new->suiv=l->t;

	l->t=new;
	if(l->taille<1) l->q=new;
	l->taille++;
	return l;
}

Listel supt_l(Listel l)
{
	if(l->t != NULL)
	{
		ListelElem tmp=l->t;
		l->t=l->t->suiv;
		freeListe(tmp->val);
		free(tmp);
		l->taille--;
	}
	return l;
}



Listel adjq_l(Listel l,S_LISTEL_CHAINE_SIMPLE a)
{
	ListelElem new=NULL;
	new=(ListelElem)malloc(sizeof(StrListelElem));

	new->val=a;
	new->suiv=NULL;

	if(l->taille<1) l->t=new;

	if(l->taille>0) l->q->suiv=new;
	l->q=new;
	l->taille++;

	return l;
}

Listel supq_l(Listel l)
{
	if(l->taille >0)
	{
		if(l->taille==1) l=supt_l(l);
		else
		{
			int i=0;
			ListelElem tmp=l->t;
			for(i=0;i < l->taille-2;i++) tmp=tmp->suiv;
			freeListe(l->q->val);
			free(l->q);
			l->q=tmp;
			tmp->suiv=NULL;
		}
	}
	return l;
}

Listel remplacer_l(Listel l,S_LISTEL_CHAINE_SIMPLE a,int indice)
{
	int i=0;
	ListelElem tmp=l->t;

	for(i=0;i<indice;i++) tmp=tmp->suiv;
	tmp->val=a;
	return l;
}

S_LISTEL_CHAINE_SIMPLE tete_l(Listel l)
{
	return l->t->val;
}

S_LISTEL_CHAINE_SIMPLE dernier_l(Listel l)
{
	return l->q->val;
}

 //La liste commence à 0, pas de liste vide
S_LISTEL_CHAINE_SIMPLE ieme_l(Listel l,int i)
{
	ListelElem tmp=l->t;
	int j=0;
	while((tmp!=NULL)&&(j<i))
	{
		tmp=tmp->suiv;
		j++;
	}
	return tmp->val;
}

int estvide_l(Listel l)
{
	return (l->taille > 0);
}

int tailleliste_l(Listel l)
{
	return l->taille;
}


void afficherliste_l(Listel l)
{
	ListelElem tmp=l->t;
	int i=0;
    for(i=0;i<l->taille;i++)
    {
        afficherliste(tmp->val);
        tmp=tmp->suiv;
    }
    printf("\n");
}

Listel inserer_l(Listel l,S_LISTEL_CHAINE_SIMPLE a,int indice)
{
	if(indice<0) l=adjt_l(l,a);
	else
	{
		if(indice>l->taille) indice=l->taille;

		ListelElem tmp=l->t,new=NULL;
		int i=0;
		for(i=0;i<indice;i++)tmp=tmp->suiv;

		new=(ListelElem)malloc(sizeof(StrListelElem));
		new->val=a;
		new->suiv=tmp->suiv;
		tmp->suiv=new;
		l->taille++;
	}
	return l;
}

Listel supprVal_l(Listel l,S_LISTEL_CHAINE_SIMPLE a)
{
	if(l->t != NULL)
	{
		if(l->t->val == a) l=supt_l(l);
		else
		{
			ListelElem tmp=l->t;
			int stop=1;
			while((tmp->suiv !=NULL) && stop)
			{
				if(tmp->suiv->val == a) stop=0;
				else tmp=tmp->suiv;
			}
			if(!stop)
			{
				ListelElem tmpfree=tmp->suiv;
				tmp->suiv=tmp->suiv->suiv;
				free(tmpfree);
			}
			l->taille--;
		}
	}
	return l;
}
Listel supprIndice_l(Listel l,int indice)
{
	if((indice < l->taille) && (indice >=0))
	{
		if(indice==0) l=supt_l(l);
		else
		{
			int i=0;
			ListelElem tmp=l->t,tmpfree=NULL;
			for(i=0;i<indice-1;i++)	tmp=tmp->suiv;
			tmpfree=tmp->suiv;
			tmp->suiv=(tmp->suiv)->suiv;
			free(tmpfree);
			l->taille--;
		}
	}

	return l;
}

int indice_l(Listel l,S_LISTEL_CHAINE_SIMPLE a)
{
	int i=0,indice=-1;
	ListelElem tmp=l->t;
	while((tmp != NULL) && (indice==-1))
	{
		if(tmp->val == a) indice=l->taille-i;
		tmp=tmp->suiv;
		i++;
	}
	return indice;
}

ListelElem adresseIeme_l(Listel l,int i)
{
	ListelElem tmp=l->t;
	while((tmp!=NULL)&&(i>0))
	{
		tmp=tmp->suiv;
		i--;
	}
	return tmp;
}

int estdans_l(Listel l,S_LISTEL_CHAINE_SIMPLE a)
{
	return (indice_l(l,a) != -1);
}

void freeListe_l(Listel l)
{
	ListelElem tmp=NULL;
	while(l->t != NULL)
	{
		tmp=l->t;
		l->t=l->t->suiv;
		freeListe(tmp->val);
		free(tmp);
	}
	free(l);
}

Listel copieListe_l(Listel l)
{
	ListelElem tmp=l->t;
	Listel new=listenouv_l();
	while(tmp != NULL)
	{
		adjq_l(new,copieListe(tmp->val));
		tmp=tmp->suiv;
	}
	return new;
}

Listel randomListeTrie_l(int n)
{
	Listel l=listenouv_l();
	int i=0;
	for(i=0;i<n;i++)
	{
		adjt_l(l,randomListeTrie((rand() %(MAX-MIN) + MIN)));
	}
	return l;
}
