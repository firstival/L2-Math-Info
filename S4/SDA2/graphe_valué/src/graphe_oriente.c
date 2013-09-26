#include "graphe_oriente.h"

Listearc newArc(S_GRAPHE_ORIENTE v,S_GRAPHE_VALUATION va)
{
	Listearc new=NULL;
	new=malloc(sizeof(Strarc));
	new->v=v;
	new->va=va;
	new->succ=NULL;
	return new;
}

Listearc insertion_1(Listearc l,S_GRAPHE_ORIENTE v,S_GRAPHE_VALUATION va)
{
	Listearc new=NULL,tmp=l;
	new=newArc(v,va);
	if(l==NULL) l=new;//Si il n'y a aucun élément
	else
	{
		if(v< (l->v))//insertion en 1er place
		{
			new->succ=l;
			l=new;
		}
		else//insertion en ieme ou dernière place
		{
			while((tmp->succ!=NULL)&&(v>(tmp->succ->v))) tmp=tmp->succ;
			if(tmp->v != v)//Unicité de l'élément
			{
				new->succ=tmp->succ;
				tmp->succ=new;
			}
		}
	}
	return l;
}

Listearc sup_1(Listearc l,S_GRAPHE_ORIENTE v)
{
	Listearc tmp=l,toDelete;
	if(l!=NULL)//Liste non vide
	{
		if(l->v==v)//Suppression du 1er élément
		{
			l=tmp->succ;
			free(tmp);
		}
		else//Suppression du ieme élément
		{
			while((tmp->succ!=NULL) && (tmp->succ->v != v)) tmp=tmp->succ;
			if(tmp->succ!=NULL)
			{
				toDelete=tmp->succ;
				tmp->succ=tmp->succ->succ;
				free(toDelete);
			}
		}
	}
	return l;
}

Listearc supall_1(Listearc l)
{
	Listearc tmp=l,tmp2=NULL;
	while(tmp!=NULL)
	{
		tmp2=tmp->succ;
		free(tmp);
		tmp=tmp2;
	}
	return NULL;
}
		

Listearc rech_1(Listearc l,S_GRAPHE_ORIENTE v)
{
	Listearc tmp=l;
	if(l!=NULL)
	{
		while((tmp!=NULL) && (tmp->v!=v)) tmp=tmp->succ;
	}
	return tmp;
}


Graphe newSommet(S_GRAPHE_ORIENTE v)
{
	Graphe new=NULL;
	new=malloc(sizeof(Strsom));
	new->v=v;
	new->suiv=NULL;
	new->ls=NULL;
	return new;
}

Graphe insertion_2(Graphe g,S_GRAPHE_ORIENTE v)
{
	Graphe new=NULL,tmp=g;
	new=newSommet(v);
	if(g==NULL) g=new;//Si il n'y a aucun élément
	else
	{
		if(v< (g->v))//insertion en 1er place
		{
			new->suiv=g;
			g=new;
		}
		else//insertion en ieme ou dernière place
		{
			while((tmp->suiv !=NULL)&&(v > (tmp->suiv->v))) tmp=tmp->suiv;
			if(tmp->v != v)//Unicité de l'élément
			{
				new->suiv=tmp->suiv;
				tmp->suiv=new;
			}
		}
	}
	return g;
}

Graphe sup_2(Graphe g,S_GRAPHE_ORIENTE v)
{
	Graphe tmp=g,toDelete;
	if(g!=NULL)//Liste non vide
	{
		if(g->v==v)//Suppression du 1er élément
		{
			free(g);
			g=NULL;
		}
		else//Suppression du 1eme élément
		{
			while((tmp->suiv!=NULL) && (tmp->suiv->v!=v)) tmp=tmp->suiv;
			if(tmp->suiv!=NULL)
			{
				toDelete=tmp->suiv;
				tmp->suiv=tmp->suiv->suiv;
				free(toDelete);
			}
		}
	}
	return g;
}



Graphe rech_2(Graphe g,S_GRAPHE_ORIENTE v)
{
	Graphe tmp=g;
	if(g!=NULL)
	{
		while((tmp!=NULL) && (tmp->v!=v)) tmp=tmp->suiv;
	}
	return tmp;
}
	

Graphe grnouv()
{
	return NULL;
}

Graphe adjs(Graphe g,S_GRAPHE_ORIENTE x)
{
	return insertion_2(g,x);
}

Graphe adja(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y,S_GRAPHE_VALUATION va)
{
	Graphe tmp=rech_2(g,x);
	tmp->ls=insertion_1(tmp->ls,y,va);
	return g;
}

int exs(Graphe g,S_GRAPHE_ORIENTE x)
{
	return (rech_2(g,x) != NULL);
}

int exa(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y)
{
	int resultat=0;
	Graphe tmp=rech_2(g,x);
	if(tmp!=NULL) resultat=(rech_1(tmp->ls,y) != NULL);
	return resultat;
}

Graphe sups(Graphe g,S_GRAPHE_ORIENTE x)
{
	g=supsuc(g,x);
	g=suppred(g,x);
	g=sup_2(g,x);
	return g;
}

Graphe supa(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y)
{
	Graphe tmp=rech_2(g,x);
	tmp->ls=sup_1(tmp->ls,y);
	return g;
}

int nb_sommet(Graphe g)
{
	int i=0;
	while(g!=NULL)
	{
		i++;
		g=g->suiv;
	}
	return i;
}

void afficheGraphe(Graphe g)
{
	Graphe tmp=NULL;
	Listearc tmparc=NULL;
	tmp=g;
	while(tmp != NULL)
	{
		printf("Sommet %d , Arc : ",tmp->v);
		tmparc=tmp->ls;
		while(tmparc != NULL)
		{
			printf("(%d,%d) ",tmp->v,tmparc->v);
			tmparc=tmparc->succ;
		}
		printf("\n");
		tmp=tmp->suiv;
	}
	printf("\n");
	return;
}


Listearc lsuc(Graphe g,S_GRAPHE_ORIENTE x)
{
	Graphe tmp=rech_2(g,x);
	Listearc tmparc=tmp->ls;
	Listearc liste=NULL,queue=NULL,new=NULL;
	if(tmparc != NULL)
	{
		new=malloc(sizeof(Strarc));
		new->v=tmparc->v;
		new->succ=NULL;
		
		liste=new;
		queue=new;
		
		tmparc=tmparc->succ;
		while(tmparc != NULL)
		{
			new=malloc(sizeof(Strarc));
			new->v=tmparc->v;
			new->succ=NULL;
			queue->succ=new;
			queue=new;
			tmparc=tmparc->succ;
		}
	}
	return liste;
}

Listearc lpred(Graphe g,S_GRAPHE_ORIENTE x)
{
	Listearc liste=NULL,queue=NULL,new=NULL;
	Graphe tmp=g;
	

	while(tmp!=NULL)
	{
		if(rech_1(tmp->ls,x) != NULL)
		{
			new=malloc(sizeof(Strarc));
			new->v=tmp->v;
			new->succ=NULL;
			if(liste == NULL)
			{
				liste = new;
				queue = new;
			}
			else
			{
				queue->succ=new;
				queue=new;
			}
		}
		tmp=tmp->suiv;
	}
	return liste;
}

int de(Graphe g,S_GRAPHE_ORIENTE x)
{
	Graphe tmp=g;
	int i=0;
	

	while(tmp!=NULL)
	{
		if(rech_1(tmp->ls,x) != NULL) i++;
		tmp=tmp->suiv;
	}
	return i;
}

int di(Graphe g,S_GRAPHE_ORIENTE x)
{
	Graphe tmp=rech_2(g,x);
	Listearc tmparc=tmp->ls;
	int i=0;
	
	while(tmparc != NULL)
	{
		i++;
		tmparc=tmparc->succ;
	}
	return i;
}

Graphe supsuc(Graphe g,S_GRAPHE_ORIENTE x)
{
	Graphe tmp=rech_2(g,x);
	tmp->ls=supall_1(tmp->ls);
	return g;
}

Graphe suppred(Graphe g,S_GRAPHE_ORIENTE x)
{
	Graphe tmp=g;
	while(tmp != NULL)
	{
		tmp->ls=sup_1(tmp->ls,x);
		tmp=tmp->suiv;
	}
	return g;
}

Graphe prim(Graphe g)
{
	S_GRAPHE_ORIENTE * sommet_restant=NULL;
	int n=nb_sommet(g),i=0;
	sommet_restant=malloc(n*sizeof(S_GRAPHE_ORIENTE));
	Graphe tmp=g;
	arc arctmp;
	Graphe a=NULL;
	for(i=0;i<n;i++)
	{
		sommet_restant[i]=tmp->v;
		tmp=tmp->suiv;
	}
	
	a=adjs(a,sommet_restant[0]);
	sommet_restant[0]=-1;
	
	i=n-1;
	while(i>0)
	{
		arctmp=rech_sommet_sortant_minimisant(sommet_restant,g,a);
		if((arctmp.x==-1) && (arctmp.y!=-1)
		{
			
		
		
		i--;
	}
}

arc rech_sommet_sortant_minimisant(S_GRAPHE_ORIENTE * sommet_restant,int nb_sommet,Graphe g,Graphe a)
{
	arc a={-1,-1,-1};
	int i=0;
	couple c={-1,-1},ctmp;
	int premier_passage=1;
	while(i<nb_sommet)
	{
		while(sommet_restant[i]==-1 && i<nb_sommet) i++;
		if(i<nb_sommet)
		{
			if(premier_passage) c=rech_couple_mini(sommet_restant[i],g,a);
			else
			{
				ctmp=rech_couple_mini(sommet_restant[i],g,a);
				if(ctmp.v<c.v) c=ctmp;
			}
			a.y=i;
		}
	}
	if(c.x != -1)
	{
		for(i=0;i<nb_sommet;i++) if(c.x==sommet_restant[i]) break;
		a.x=i;
		a.va=c.v;
	}
	return a;
}
couple rech_couple_mini(S_GRAPHE_ORIENTE z,Graphe g,Graphe a)
{
	couple c={-1,-1};
	int premier_passage=1;
	Listearc lp=NULL,toDelete;
	lp=lpred(g,z);
	if(lp != NULL)
	{
		do
		{
			if(exs(a,lp->v))
			{
				if(premier_passage)
				{
					c.v=lp->va;
					c.x=lp->v;
					premier_passage=0;
				}
				else if(c.v>lp->va)
				{
					c.v=lp->va;
					c.x=lp->v;
				}
				toDelete=lp;
				lp=lp->succ;
				free(toDelete);
			}
		}
		while(lp != NULL);
	
	return c;
}
