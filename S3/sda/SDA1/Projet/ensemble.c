/** \file
 * \author Thomas Kuntz
 * Ensemble : Source
 * */

#include "ensemble.h"


Ens EnsAlloc()
{
    Ens E=NULL;
    E=(Ens)malloc(sizeof(StrEns));
    E->taille=0;
    E->taillemax=MAXENS;
    E->tab=(pCouple)malloc(MAXENS * sizeof(Couple));
    return E;
}

void EnsFree(Ens E)
{
    free(E->tab);
    free(E);
}

int EnsEstVide(Ens E)
{
    return (E->taille==0);
}

Ens EnsAjoute(Ens E,Couple c)
{
    if(E->taille==E->taillemax)
    {
        E->tab=(pCouple)realloc(E->tab, (E->taillemax + MAXENS)*sizeof(Couple));
        E->taillemax+=MAXENS;
    }
    E->tab[E->taille]=c;
    E->taille++;
    return E;
}

int EnsRechercheCouple(Ens E,Couple c)
{
    int i=0;
    while((i != E->taille) && (compareCouple(c,E->tab[i]) != 1)) i++;
    if(compareCouple(c,E->tab[i]) != 1) i=-1;
    return i;
}

Ens SupprIeme(Ens E,int i)
{
    if((0 <= i) && (i < E->taille))
    {
        if(i != (E->taille-1)) E->tab[i]=E->tab[E->taille-1];
        E->taille--;
    }
    return E;
}


Ens EnsSuppr(Ens E,Couple c)
{
    int i=EnsRechercheCouple(E,c);
    E=SupprIeme(E,i);
    return E;
}

Ens EnsSupprDernier(Ens E)
{
    E=SupprIeme(E,E->taille-1);
    return E;
}

int EnsEstDans(Ens E,Couple c)
{
    int i = EnsRechercheCouple(E,c);
    return (i!=-1);
}

int EnsTaille(Ens E)
{
    return E->taille;
}

Couple EnsTirage(Ens E)
{
    int tirage=(rand() % E->taille);
    Couple tmp=E->tab[tirage];
    E=SupprIeme(E,tirage);
    return tmp;
}
