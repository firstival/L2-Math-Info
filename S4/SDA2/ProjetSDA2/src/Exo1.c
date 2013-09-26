#include "Exo1.h"

Liste inter1(Liste l1,Liste l2)
{
	Liste ltmp=copieListe(l1),l=copieListe(l2);//Copie des listes passées en paramètre
	while(tailleliste(ltmp)>0)
	{
		insav(l,tete(ltmp));
		supt(ltmp);
	}
	freeListe(ltmp);
	return l;
}


Liste inter2(Liste l1,Liste l2)
{
	Liste l=NULL;
	if(tailleliste(l1)==0) l=copieListe(l2);
	else if(tailleliste(l2)==0) l=copieListe(l1);
	else
	{
		l=listenouv();
		Liste l1c=copieListe(l1), l2c=copieListe(l2);//Copie des listes passées en argument
		S_LISTE_CHAINE_SIMPLE x,y;

		while((tailleliste(l1c)>0)&&(tailleliste(l2c)>0))//Tant qu'aucune des deux listes n'est vide
		{
			x=tete(l1c);
			y=tete(l2c);

			if(x < y)
			{
				adjq(l,x);
				supt(l1c);
			}
			else
			{
				adjq(l,y);
				supt(l2c);
			}
		}
		while(tailleliste(l1c)>0)//Si a la sortie de la premiere boucle, il reste des éléments dans l1c, on copie le reste dans l
		{
			adjq(l,tete(l1c));
			supt(l1c);
		}
		while(tailleliste(l2c)>0)//Si a la sortie de la premiere boucle, il reste des éléments dans l2c, on copie le reste dans l
		{
			adjq(l,tete(l2c));
			supt(l2c);
		}
		freeListe(l2c);
		freeListe(l1c);
	}
	return l;
}

Liste interk1(Listel l)
{
    Liste lfinal=NULL;
    if(tailleliste_l(l)<=0) lfinal=listenouv();
    else if(tailleliste_l(l)==1)lfinal=copieListe(tete_l(l));
    else
    {
        Listel ltmp=copieListe_l(l);
        Liste l1=NULL,l2=NULL,l3=NULL;

        l1=tete_l(ltmp);
        l2=ieme_l(ltmp,1);

        l2=inter2(l1,l2);

        supt_l(ltmp);
        supt_l(ltmp);

        while(tailleliste_l(ltmp)>0)
        {
            l1=tete_l(ltmp);
            l3=inter2(l1,l2);
            supt_l(ltmp);
            freeListe(l2);
            l2=l3;
        }
        lfinal=l2;
        freeListe_l(ltmp);
    }

    return lfinal;
}


Liste interk2(Listel l)
{
    Liste lfinal=NULL;
    if(tailleliste_l(l)<=0) lfinal=listenouv();
    else if(tailleliste_l(l)==1)lfinal=copieListe(tete_l(l));
    else
    {
        Listel tmp=listenouv_l();
        Listel lc=copieListe_l(l);
        Liste l1=NULL,l2=NULL;

        while(tailleliste_l(lc)>1)//Premier passage, pour amorcer la liste tmp, vu que adjt_l ne copie pas la liste passé en argument
        {
            l1=tete_l(lc);
            l2=ieme_l(lc,1);
            adjq_l(tmp,inter2(l1,l2));
            supt_l(lc);
            supt_l(lc);
        }
        if(tailleliste_l(lc)==1)// Si le nombre de liste est impaire, il reste une liste dans lc
        {
			adjt_l(tmp,copieListe(tete_l(lc)));
			supt_l(lc);
		}
        freeListe_l(lc);

        while(tailleliste_l(tmp)>1)
        {
            l1=tete_l(tmp);
            l2=ieme_l(tmp,1);
            adjq_l(tmp,inter2(l1,l2));
            supt_l(tmp);
            supt_l(tmp);
        }

        lfinal=copieListe(tete_l(tmp));

        freeListe_l(tmp);
    }
    return lfinal;
}

Liste liste1()
{
	Liste l=listenouv();
	l=adjt(l,15);
	l=adjt(l,13);
	l=adjt(l,9);
	l=adjt(l,7);
	l=adjt(l,3);
	return l;
}

Liste liste2()
{
	Liste l=listenouv();
	l=adjt(l,14);
	l=adjt(l,10);
	l=adjt(l,6);
	l=adjt(l,4);
	return l;
}

Listel listeliste()
{
	Listel ll=listenouv_l();
	Liste l1=listenouv();
	Liste l2=listenouv();
	Liste l3=listenouv();
	Liste l4=listenouv();
	Liste l5=listenouv();

	l1=adjt(l1,10);
	l1=adjt(l1,6);
	l1=adjt(l1,4);
	l1=adjt(l1,2);

	l2=adjt(l2,11);
	l2=adjt(l2,7);
	l2=adjt(l2,6);
	l2=adjt(l2,3);

	l3=adjt(l3,12);
	l3=adjt(l3,8);
	l3=adjt(l3,7);
	l3=adjt(l3,3);

	l4=adjt(l4,15);
	l4=adjt(l4,12);
	l4=adjt(l4,10);
	l4=adjt(l4,7);
	l4=adjt(l4,3);

	l5=adjt(l5,12);
	l5=adjt(l5,8);
	l5=adjt(l5,7);
	l5=adjt(l5,5);
	l5=adjt(l5,4);

	ll=adjt_l(ll,l5);
	ll=adjt_l(ll,l4);
	ll=adjt_l(ll,l3);
	ll=adjt_l(ll,l2);
	ll=adjt_l(ll,l1);

	return ll;
}

int main()
{
    Liste l1=liste1();
    Liste l2=liste2();
    Liste l3=inter1(l1,l2);
    Liste l4=inter2(l1,l2);
    printf("Liste 1:\n");
    afficherliste(l1);
    printf("Liste 2:\n");
    afficherliste(l2);
    printf("Inter1 sur Liste1 et Liste2\n");
    afficherliste(l3);
    printf("Inter2 sur Liste1 et Liste2\n");
    afficherliste(l4);

    printf("\n\n");

    Listel ll=listeliste();
    printf("Une liste de k liste triees :\n");
    afficherliste_l(ll);
    printf("Interk1 sur cette liste de liste :\n");
    Liste lfinal1=interk1(ll);
    afficherliste(lfinal1);
    printf("Interk2 sur cette liste de liste :\n");
    Liste lfinal2=interk2(ll);
    afficherliste(lfinal2);

    freeListe(l1);
    freeListe(l2);
    freeListe(l3);
    freeListe(l4);
    freeListe(lfinal1);
    freeListe(lfinal2);

    freeListe_l(ll);
    return 0;
}
