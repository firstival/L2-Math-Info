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

	if(l->taille>0) l->q->suiv=new;
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
 //La liste commence à 0, pas de liste vide
S_LISTE_CHAINE_SIMPLE ieme(Liste l,int i)
{
	ListeElem tmp=l->t;
	int j=0;
	while((tmp!=NULL)&&(j<i))
	{
		tmp=tmp->suiv;
		j++;
	}
	return tmp->val;
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
		printf("%d | ", tmp->val);
		tmp=tmp->suiv;
	}
	if(l->taille > 0) printf("%d",l->q->val);
	printf("\n");
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

Liste supprVal(Liste l,S_LISTE_CHAINE_SIMPLE a)
{
	if(l->t != NULL)
	{
		if(l->t->val == a) l=supt(l);
		else
		{
			ListeElem tmp=l->t;
			int stop=1;
			while((tmp->suiv !=NULL) && stop)
			{
				if(tmp->suiv->val == a) stop=0;
				else tmp=tmp->suiv;
			}
			if(!stop)
			{
				ListeElem tmpfree=tmp->suiv;
				tmp->suiv=tmp->suiv->suiv;
				free(tmpfree);
			}
			l->taille--;
		}
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

int indice(Liste l,S_LISTE_CHAINE_SIMPLE a)
{
	int i=0,indice=-1;
	ListeElem tmp=l->t;
	while((tmp != NULL) && (indice==-1))
	{
		if(tmp->val == a) indice=l->taille-i;
		tmp=tmp->suiv;
		i++;
	}
	return indice;
}

ListeElem adresseIeme(Liste l,int i)
{
	ListeElem tmp=l->t;
	while((tmp!=NULL)&&(i>0))
	{
		tmp=tmp->suiv;
		i--;
	}
	return tmp;
}

Liste insav(Liste l,S_LISTE_CHAINE_SIMPLE a)
{
	if(l->taille==0) adjt(l,a);
	else if(a<(l->t->val)) adjt(l,a);
	else
	{
		ListeElem tmp=l->t;
		while((tmp->suiv != NULL)&&(tmp->suiv->val < a)) tmp=tmp->suiv;


		if(tmp == l->q) adjq(l,a);
		else
		{	
			ListeElem new=(ListeElem)malloc(sizeof(StrListeElem));

			new->val=a;
			new->suiv=tmp->suiv;
			tmp->suiv=new;
			l->taille++;
		}
	}

	return l;
}

int estdans(Liste l,S_LISTE_CHAINE_SIMPLE a)
{
	return (indice(l,a) != -1);
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


Liste copieListe(Liste l)
{
	ListeElem tmp=l->t;
	Liste l2=listenouv();

	while(tmp != NULL)
	{
		adjq(l2,tmp->val);
		tmp=tmp->suiv;
	}

	return l2;
}

Liste randomListeTrie(int n)
{
	int i=0;
	int e=0;
	Liste l=listenouv();
	for(i=0;i<n;i++)
	{
	    e+=(rand() %(LISTE_RAND_MAX-1)) +1;
		adjq(l,e);
	}
	return l;
}
