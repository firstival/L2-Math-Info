#include "Exo3.h"

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

Listet desd(TournoiBinPos a,Listet p)
{
	TournoiBinPos tmp=a;
	while(tmp!=NULL)
	{
		p=adjt_t(p,tmp);
		tmp=ad(tmp);
	}
	return p;
}

TournoiBinPos tournoinouv()
{
    return NULL;
}


TournoiBinPos e(TournoiBinPos g,int n,S_TOURNOI_POSITION x,TournoiBinPos d)
{
    TournoiBinPos t=malloc(sizeof(StrTournoiBinPos));
    t->g=g;
    t->d=d;
    t->v=x;
    t->n=n;
    return t;
}


S_TOURNOI_POSITION r(TournoiBinPos a)
{
    return a->v;
}


TournoiBinPos ag(TournoiBinPos a)
{
    if(a==NULL) return NULL;
    else return a->g;
}


TournoiBinPos ad(TournoiBinPos a)
{
    if(a==NULL) return NULL;
    else return a->d;
}


int v(TournoiBinPos a)
{
    return (a==NULL);
}


int nn(TournoiBinPos a)
{
    int n=0;
    if(a!=NULL)n=a->n;
    return n;
}


int hauteur(TournoiBinPos a)
{
	int total=0,i=0,indice=0,k=0,bit=0;
	Listet l=listenouv_t();
	l=adjt_t(l,a);
	while(l.taille !=total)
	{
		total=l.taille;
		for(i=indice;i<total;i++)
		{
			if(l.tab[i]->g!=NULL)
			{
				l=adjt_t(l,l.tab[i]->g);
				bit=1;
			}
			if(l.tab[i]->d!=NULL)
			{
				l=adjt_t(l,l.tab[i]->d);
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
	freeListe_t(l);
	return k;
}

void freeTournoi(TournoiBinPos t)
{
	if(t!=NULL)
	{
		freeTournoi(ag(t));
		freeTournoi(ad(t));
		free(t);
	}
	return;
}

TournoiBinPos copieTournoi(TournoiBinPos t)
{
    if(t==NULL) return NULL;
    else
    {
        return e(copieTournoi(t->g),t->n,t->v,copieTournoi(t->d));
    }
}



void printTab(int k)
{
	int i=0;
	for(i=0;i<k;i++) printf("   ");
}

void afficherValeurArbre(TournoiBinPos a)
{
	printf("%d|%d",r(a),a->n);
}

void afficherTournoi(TournoiBinPos a)
{
	int h=hauteur(a);
	int n=pow2(h+1)-1;
	int k=1;
	int z=n;
	TournoiBinPos * t=(TournoiBinPos *)malloc(n*sizeof(TournoiBinPos));
	int i=0,j=1;
	t[0]=a;
	for(i=0;j<n;i++)//Création du tas
	{
		if(t[i]!=NULL)
		{

			t[j]=ag(t[i]);
			t[j+1]=ad(t[i]);
		}
		else
		{
			t[j]=ag(NULL);
			t[j+1]=ad(NULL);
		}

		j+=2;
	}
	i=0;
	while(i<n)
	{
		printTab(z);
		for(i=i;i<k;i++)//Affichage du tas
		{
			if(t[i]==NULL) printf("   ");
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




int imin(Liste l,int j,int k)
{
    int i=0,imini=j;
    S_LISTE_CONTIGU min=ieme(l,j),tmp;
    for(i=j;i<=k;i++)
    {
        tmp=ieme(l,i);
        if(tmp<min)
        {
            min=tmp;
            imini=i;
        }
    }
    return imini;
}


TournoiBinPos la(Liste l)
{
    if(estvide(l)) return tournoinouv();
    else
    {
        int i=0,j=tailleliste(l)-1;
        return la_aux(l,i,j);
    }
}

TournoiBinPos la_aux(Liste l,int i,int j)
{
    if(i>j) return NULL;
    else
    {
        int k=imin(l,i,j);
        return e(la_aux(l,i,k-1),j-i+1,ieme(l,k),la_aux(l,k+1,j));
    }
}


Liste al(TournoiBinPos a)//Parcours infixe inverse : d r g
{
    Liste l=listenouv();
    Listet tmp=listenouv_t();
    TournoiBinPos atmp;
    tmp=desd(a,tmp);
    while(tailleliste_t(tmp)>0)
    {
        atmp=tete_t(tmp);
        tmp=supt_t(tmp);
        l=adjt(l,r(atmp));
        tmp=desd(ag(atmp),tmp);
    }
    freeListe_t(tmp);
    return l;
}

//Premier element : position 1
S_TOURNOI_POSITION el(TournoiBinPos a,int k)
{
    int i=0;
    if(k<1) k=1;
    else if(k>nn(a))k=nn(a);
    TournoiBinPos tmp=a;
    do
    {
        i=nn(ag(tmp))+1;
        if(i>k) tmp=ag(tmp);
        else if(i<k)
        {
            tmp=ad(tmp);
            k=k-i;
        }
    }
    while(i!=k);
    return tmp->v;
}


TournoiBinPos union1(TournoiBinPos a1,TournoiBinPos a2)
{
    if(a1==NULL) return copieTournoi(a2);
    else if(a2==NULL) return copieTournoi(a1);
    else
    {
        if(a1->v <= a2->v) return e(copieTournoi(ag(a1)),nn(a1) + nn(a2),a1->v,union1(ad(a1),a2));
        else return e(union1(a1,ag(a2)),nn(a1) + nn(a2),a2->v,copieTournoi(ad(a2)));
    }
}


CoupleTournoiBinPos coup(TournoiBinPos a,int k)//Coupe après le kieme élément
{
    CoupleTournoiBinPos c={NULL,NULL};
    CoupleTournoiBinPos ctmp={NULL,NULL};
    int i=0;
    TournoiBinPos tmp=NULL;
    if(a==NULL) return c;
    else if(k<=0)
    {
        c.a1=NULL;
        c.a2=copieTournoi(a);
        return c;
    }
    else
    {
        i=nn(ag(a))+1;
        if(i==k)
        {
            tmp=copieTournoi(a);
            c.a1=tmp;
            c.a2=ad(tmp);
            tmp->n-=nn(ad(tmp));
            tmp->d=NULL;
            return c;
        }
        else if(k<i)
        {
            ctmp=coup(ag(a),k);
            c.a1=ctmp.a1;
            c.a2=e(ctmp.a2,1+nn(ad(a))+nn(ctmp.a2),a->v,copieTournoi(ad(a)));
            return c;
        }
        else
        {
            ctmp=coup(ad(a),k-i);
            c.a1=e(copieTournoi(ag(a)),i+nn(ctmp.a1),a->v,ctmp.a1);
            c.a2=ctmp.a2;
            return c;
        }
    }
}


TournoiBinPos ins(TournoiBinPos a,S_TOURNOI_POSITION x, int k)
{
	CoupleTournoiBinPos c=coup(a,k-1);
	TournoiBinPos tmp1=e(NULL,1,x,NULL);
	TournoiBinPos tmp2=union1(c.a1,tmp1);
	TournoiBinPos tmp3=union1(tmp2,c.a2);
	freeTournoi(tmp1);
	freeTournoi(tmp2);
	freeTournoi(c.a1);
	freeTournoi(c.a2);
	return tmp3;
}

TournoiBinPos sup(TournoiBinPos a,int k)
{
    if(a==NULL) return NULL;
    else
    {
        int i=nn(ag(a))+1;
        if(i==k) return union1(ag(a),ad(a));
        else if(k<i) return e(sup(ag(a),k),nn(a)-1,a->v,copieTournoi(ad(a)));
        else return e(copieTournoi(ag(a)),nn(a)-1,a->v,sup(ad(a),k-i));
    }
}

Liste Exemple()
{
	Liste l=listenouv();
	adjt(l,7);
	adjt(l,12);
	adjt(l,3);
	adjt(l,11);
	adjt(l,6);
	adjt(l,0);
	adjt(l,5);
	adjt(l,10);
	adjt(l,2);
	adjt(l,9);
	adjt(l,4);
	adjt(l,8);
	return l;
}

int main()
{
    Liste l1=Exemple();
    printf("Liste 1 :\n");
    afficherliste(l1);

    TournoiBinPos t1=la(l1);
    printf("Tournoi binaire de position associe a Liste1:\n");
    afficherTournoi(t1);

    printf("\n5eme element du Tournoi Binaire de Position 1 : %d\n",el(t1,5));

    CoupleTournoiBinPos c=coup(t1,7);
    printf("Coupure de t1 apres le 7ieme element :\n");
    printf("1er Tournoi de la coupure :\n");
    afficherTournoi(c.a1);
    printf("2eme Tournoi de la coupure :\n");
    afficherTournoi(c.a2);

    printf("Insertion de l'element 42 dans t1 en 5eme position :\n");
    TournoiBinPos t2=ins(t1,42,5);
    afficherTournoi(t2);

    TournoiBinPos t3=sup(t1,11);
    printf("Suppression du 11eme element :\n");
    afficherTournoi(t3);

    freeListe(l1);
    freeTournoi(t1);
    freeTournoi(t2);
    freeTournoi(t3);
    freeTournoi(c.a1);
    freeTournoi(c.a2);

    return 0;
}
