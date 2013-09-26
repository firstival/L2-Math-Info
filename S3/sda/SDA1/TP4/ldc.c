/** \file ldc.c
 * listes doublement chaînées de Trucs
 */

#include "truc.h"
#include "ldc.h"

/** \memberof LDC
 * Constructeur : renvoie une nouvelle LDC (vide)
 * \param -
 * \return LDC vide
 * \pre
 * \post
 */
LDC *LDCAlloc(void)
{
	pLDC p=NULL;
	p=(pLDC)malloc(sizeof(LDC));
	p->suiv=NULL;
	p->prec=NULL;
	return p;
}

/** \memberof LDC
 * Destructeur : libère la mémoire allouée pour une LDC
 * \param[in] l une LDC
 * \return -
 * \pre
 * \post \a l ne doit pas être utiisée après cet appel
 */
void LDCFree( LDC *l )
{
	pLDC tmp=NULL;
	while(l != NULL)
	{
		tmp=l->suiv;
		free(l);
		l=tmp;
	}	
}


/** \memberof LDC
 * Constructeur : ajoute un élément à la LDC, en position courante \a l
 * \param[inout] l LDC, position d'insertion de \a t
 * \param[in] t élément à insérer
 * \return -
 * \pre
 * \post la LDC est non vide
 */
void LDCInsere( LDC **l, Truc t )
{
	pLDC new=NULL;
	new=LDCAlloc();
	new->m=t;
	new->suiv=(*l);
	new->prec=(*l)->prec;
	(*l)->prec=new;
	(*l)=new;
}

/** \memberof LDC
 * Constructeur : supprime l'élément en position courante de la LDC
 * \param[inout] l une LDC (position courante)
 * \return -
 * \pre  !LDCEstVide(l)
 * \post
 */
void LDCSupprime( LDC **l )
{
	pLDC tmp=NULL;
	tmp=(*l);
	
	(tmp->suiv)->prec=(tmp->prec);
	(tmp->prec)->suiv=(tmp->suiv);
	
	tmp=tmp->suiv;
	
	free(*l);
	(*l)=tmp;
}

/** \memberof LDC
 * Constructeur : échange l'élément courant et le suivant
 * \param [inout] l une LDC
 * \return -
 * \pre deux éléments au moins en position \a l
 * \post
 */
void LDCEchange( LDC **l )
{
	pLDC elementcourant=NULL,elementsuivant=NULL;
	elementcourant=(*l);
	elementsuivant=elementcourant->suiv;
	/*
	elementcourant->suiv=elementsuivant->suiv;
	elementsuivant->prec=elementcourant->prec;
	
	elementcourant->prec=elementsuivant;
	elementsuivant->suiv=elementcourant;
	
	(*l)=elementsuivant;*/
	Truc m=elementcourant->m;
	elementcourant->m=elementsuivant->m;
	elementsuivant->m=m;
}

/** \memberof LDC
 * Sélecteur : renvoie la position de l'élément suivant de la LDC
 * \param[in] l une LDC
 * \return position de l'élément suivant dans la LDC 
 * \pre ! LDCEstVide(l)
 * \post
 */
LDC *LDCSuivant( LDC *l )
{
	return l->suiv;
}

/** \memberof LDC
 * Sélecteur : renvoie la position de l'élément précédent de la LDC
 * \param[in] l une LDC
 * \return position de l'élément précédent dans la LDC 
 * \pre ! LDCDebut(l)
 * \post
 */
LDC *LDCPrecedent( LDC *l )
{
	return l->prec;
}

/** \memberof LDC
 * Sélecteur : teste si une LDC est vide
 * \param [in] l une LDC
 * \return vrai si la LDC est vide, faux sinon
 * \pre
 * \post
 */
int  LDCEstVide( LDC *l )
{
	return (l==NULL);
}


/** \memberof LDC
 * Sélecteur : teste si la position courante dans la LDC est la première
 * \param [in] l une LDC
 * \return vrai la position courante dans la LDC est la première, faux sinon
 * \pre
 * \post
 */
int  LDCDebut( LDC *l )
{
	return (l->prec == NULL);
}

/** \memberof LDC
 * Sélecteur : renvoie la position du iième élément d'une LDC
 * \param [in] l une LDC
 * \param [in] i un entier
 * \return position du iième élément
 * \pre 0 <= i < LDCLongueur(l)
 * \post
 */
LDC *LDCiieme( LDC *l, int i )
{
	int n=0;
	while(l->prec !=NULL)
	{
		l=l->prec;
	}
	for(n=0;n<i;n++)
	{
		l=l->suiv;
	}
	
	return l;
}

/** \memberof LDC
 * Sélecteur : longueur d'une LDC
 * \param[in] l une LDC
 * \return le nombre d'éléments de la LDC
 * \pre
 * \post
 */
int  LDCLongueur( LDC *l )
{
	int i=0;
	while(l->prec !=NULL)
	{
		l=l->prec;
	}
	if(!LDCEstVide(l))
	{
		i++;
		while(l->suiv != NULL)
		{
			l=l->suiv;
			i++;
		}
	}
	return i;		
	
}

/** \memberof LDC
 * Constructeur : normalise un polynôme contenu dans une LDC.
 * Place ses monômes dans l'ordre de leurs degrés et élimine les duplicata
 * (en faisant la somme de leurs coefs).
 * \param [inout] P polynôme à normaliser
 * \return 
 * \pre 
 * \post
 */
void Normalise( LDC **P )
{
	pLDC debut,tmp
	debut=(LDCiieme(*P,0));
	tmp=debut;
	int longueur = LDCLongueur(*P);
	int i=0,j=0;
	if(tmpongueur != 0 || tmpongueur!=1)
	{
		for(i=0;i<tmpongueur;i++)
		{
			for(j=0;j<tmpongueur;j++)
			{
				if(tmp->m.degre < (tmp->suiv)->m.degre)
				{
					tmpDCEchange(&tmp);
					tmp=tmp->suiv;
				}
			}
		}
	
		tmp=debut;
		for(i=0;i<longueur;i++)
		{
			if(tmp->m.degre == (tmp->suiv)->m.degre)
			{
				(tmp->suiv)->m.coef+=tmp->m.coef;
				LDCSupprime(&tmp);
				longueur--;
			}
			else tmp=tmp->suiv;
		}
	}
}

