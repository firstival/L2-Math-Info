
#include <stdio.h>
#include <math.h>
#include "graph.h"

#define HM 800
#define LM 1200
#define ITER 400

int main()
{
	int i,x,y;
	double cr, ci, ur, ui, u;
	long c1,c2,c3,c4, c5;

	initgraph(LM, HM);
	c1 = newcolor(0,0,0);
	c2 = newcolor(1,0,0);
	c3 = newcolor(1,1,0);
	c4 = newcolor(0,1,0);

	c5 = newcolor(0,0,1);

	for( y=0 ; y<HM ; y++ )
		for( x=0 ; x<LM ; x++ )
		{
			ur = ui = 0;
			cr = (3.*x/((double)LM))-1.;
			ci = (2.*y/((double)HM))-1.;
			for( i=0 ; i<ITER ; i++ )
			{
				u = ur;
				ur = u*u - ui*ui - cr ;
				ui = 2.*u*ui - ci;
				if( fabs(ur)>3. || fabs(ui)>3. )
					break;
			}
			if( i==ITER )
			{
				setcolor(c1);
				putpixel( x, y );
			}
			else if (i>ITER/12.5 )
			{
				setcolor(c2);
				putpixel( x, y );
			}
			else if (i>ITER/25 )
			{
				setcolor(c3);
				putpixel( x, y );
			}
			else if (i>ITER/40 )
			{
				setcolor(c4);
				putpixel( x, y );
			}
		}

	refresh();
	waitgraph();
	closegraph();
	return( 0 );
}

