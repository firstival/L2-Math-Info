/** \file
 * \author Thomas Kuntz
 * Sorte : Source
 * */
#include "sorte.h"

Couple construCouple(int x,int y)
{
	Couple c={x,y};
	return c;
}

int compareCouple(Couple c1,Couple c2)
{
    return (c1.x==c2.x && c1.y==c2.y);
}

Couple additionCouple(Couple a,Couple b)
{
    Couple c={a.x+b.x,a.y+b.y};
    return c;
}

int zeroOuUn(int x)
{
    int a;
    if(x<0)a=-1;
    else if(x==0)a=0;
    else if(x>0)a=1;
    return a;
}
