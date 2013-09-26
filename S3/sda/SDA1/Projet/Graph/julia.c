
#include <stdio.h>
#include <math.h>
#include "graph.h"

#define HM 800
#define LM 1200

#define ITER 300
#define N1 150
#define N2 80
#define N3 40
#define N4 15

#define MR .776
#define MI .119

int main()
{
	int i,x,y;
	double cr, ci, ur, ui, u;
	long c0,c1,c2,c3;

	initgraph(LM, HM);
	c0 = newcolor(0,0,0);
	c1 = newcolor(1,0,0);
	c2 = newcolor(1,1,0);
	c3 = newcolor(0,1,0);

	cr = MR;
	ci = MI;
	for( y=0 ; y<HM ; y++ )
		for( x=0 ; x<LM ; x++ )
		{
			ur = (4.*x/((double)LM))-2.;
			ui = (2.*y/((double)HM))-1.;
			for( i=0 ; i<ITER ; i++ )
			{
				u = ur;
				ur = u*u - ui*ui - cr ;
				ui = 2.*u*ui - ci;
				if( fabs(ur)>10. || fabs(ui)>10. )
					break;
			}
			if( i==ITER )
			{
				setcolor(c0);
				putpixel( x, y );
			}
			else if (i>N1 )
			{
				setcolor(c1);
				putpixel( x, y );
			}
			else if (i>N2 )
			{
				setcolor(c2);
				putpixel( x, y );
			}
			else if (i>N3 )
			{
				setcolor(c3);
				putpixel( x, y );
			}
		}
	refresh();

	waitgraph();
	closegraph();
	return( 0 );
}

