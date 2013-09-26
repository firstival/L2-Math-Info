#include "Exo2.h"

int imin(Liste l,int j,int k)
{
    int i=0,imini=j;
    ARBRE_BIN_S min=ieme(l,j),tmp;
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


Arbin la(Liste l)
{
    if(estvide(l)) return newArbin();
    else
    {
        int i=0,j=tailleliste(l)-1;
        return la_aux(l,i,j);
    }
}

Arbin la_aux(Liste l,int i,int j)
{
	if(i>j) return NULL;
    else
    {
        int k=imin(l,i,j);
        return e(la_aux(l,i,k-1),ieme(l,k),la_aux(l,k+1,j));
    }
}


Liste al(Arbin a)//Parcours infixe inverse : d r g
{
    Liste l=listenouv();
    Listea tmp=listenouv_a();
    Arbin atmp;
    tmp=desd(a,tmp);
    while(tailleliste_a(tmp)>0)
    {
        atmp=tete_a(tmp);
        tmp=supt_a(tmp);
        l=adjt(l,rac(atmp));
        tmp=desd(ag(atmp),tmp);
    }
    freeListe_a(tmp);
    return l;
}


Arbin union0(Arbin a1,Arbin a2)
{
    Liste l1=al(a1);
    Liste l2=al(a2);
    Liste l=concat(l1,l2);
    Arbin a=la(l);
    freeListe(l);
    freeListe(l1);
    freeListe(l2);
    return a;
}


Arbin union1(Arbin a1,Arbin a2)// Ici, la fonction copieArbre permet de rendre la methode fonctionnelle
{
    if(a1==NULL) return copieArbre(a2);
    else if(a2==NULL) return copieArbre(a1);
    else
    {
        if(a1->v <= a2->v) return e(copieArbre(ag(a1)),a1->v,union1(ad(a1),a2));
        else return e(union1(a1,ag(a2)),a2->v,copieArbre(ad(a2)));
    }
}


Arbin om(Arbin a)
{
    Arbin atmp=union1(ag(a),ad(a));
    return atmp;
}


Arbin ins(Arbin a,ARBRE_BIN_S x)
{
    Arbin tmp=e(NULL,x,NULL);
    Arbin u=union1(a,tmp);
    free(tmp);
    return u;
}

Liste Exemple1()
{
	Liste l=listenouv();
	l=adjt(l,11);
	l=adjt(l,4);
	l=adjt(l,10);
	l=adjt(l,1);
	l=adjt(l,9);
	l=adjt(l,3);
	l=adjt(l,8);

	return l;
}

Liste Exemple2()
{
	Liste l=listenouv();
	l=adjt(l,7);
	l=adjt(l,14);
	l=adjt(l,2);
	l=adjt(l,13);
	l=adjt(l,5);
	l=adjt(l,15);

	return l;
}

int main()
{
    Liste l1=Exemple1();
    Liste l2=Exemple2();
    printf("Liste1 de 7 elements :\n");
    afficherliste(l1);
    printf("Liste2 de 6 elements :\n");
    afficherliste(l2);


    Arbin a1=la(l1);
    Arbin a2=la(l2);
    printf("Affichage de l'arbre1\n");
    afficherArbre(a1);
    printf("Affichage de l'arbre2\n");
    afficherArbre(a2);
    printf("\n");

    Liste l3=al(a1);
    printf("al sur arbre1 :\n");
    afficherliste(l3);

    Arbin u0=union0(a1,a2);
    Arbin u1=union1(a1,a2);

    printf("Affichage de union0 :\n");
    afficherArbre(u0);

    printf("Affichage de union1 :\n");
    afficherArbre(u1);

    printf("Oter le minimum de l'arbre1\n");
    Arbin o=om(a1);
    afficherArbre(o);

    Arbin i=ins(a1,42);
    printf("Insertion de 42 dans l'arbre1\n");
    afficherArbre(i);

    freeListe(l1);
    freeListe(l2);
    freeListe(l3);

    freeArbre(a1);
    freeArbre(a2);
    freeArbre(u0);
    freeArbre(u1);
    freeArbre(o);
    freeArbre(i);


    return 0;
}
