
#include <stdio.h>
#include "graph.h"

#define CARRE 3
#define INTER 0

#define HM 300
#define LM 200
#define ITER 10000

/* longueur cycle recherche - 1 */
#define LONGCYCLE 11

struct tab
{
	int l,h;
	char cell[HM][LM];
};

struct tab init( int, int );
void calcnouv( struct tab *, struct tab * );
void affiche( struct tab *);

int main()
{
	struct tab t[LONGCYCLE]; int i;

	t[0] = init(HM, LM);

	initgraph(HM*(CARRE+INTER), LM*(CARRE+INTER));

	for( i=0 ; i<ITER ; i++ )
	{
/*		if(i%10==0) */
			affiche( &t[i%LONGCYCLE] );
		calcnouv( &t[i%LONGCYCLE], &t[(i+1)%LONGCYCLE] );

	}
	closegraph();
	return( 0 );
}

struct tab init( int h, int l )
{
	int i,j;
	struct tab t;
	srand(time(0));
	for( i=0 ; i<h ; i++ )
		for( j=0 ; j<l ; j++ )
		{
/*			t.cell[i][j] = rand()%2;  */
/*			t.cell[i][j] = ((i+j)%3==0)?1:0; */
/*			t.cell[i][j] = (i==0||j==0||i==h-1||j==l-1)?0:1; */
			t.cell[i][j] = 0;
		}
	t.cell[10][10] = 1;
	t.cell[10][11] = 1;
	t.cell[10][12] = 1;
	t.cell[9][12] = 1;
	t.cell[8][11] = 1;

	t.cell[55][50] = 1;
	t.cell[54][51] = 1;
	t.cell[54][52] = 1;
	t.cell[55][53] = 1;
	t.cell[56][50] = 1;
	t.cell[56][51] = 1;
	t.cell[56][52] = 1;
	t.l = l;
	t.h = h;
	return( t );
}

int nbvois( struct tab *t, int i, int j )
{
	int n=0;
	if( i>0 )
	{	/* i-1 */
		if( j>0 )
			if( t->cell[i-1][j-1] )
				n++;
		if( t->cell[i-1][j] )
				n++;
		if( j<t->l-1 )
			if( t->cell[i-1][j+1] )
				n++;
	}
	if( j>0 )
		if( t->cell[i][j-1] )
			n++;
	if( j<t->l-1 )
		if( t->cell[i][j+1] )
			n++;
	if( i<t->h-1 )
	{	/* i+1 */
		if( j>0 )
			if( t->cell[i+1][j-1] )
				n++;
		if( t->cell[i+1][j] )
				n++;
		if( j<t->l-1 )
			if( t->cell[i+1][j+1] )
				n++;
	}
	return( n );
}

void calcnouv( struct tab *t, struct tab *n )
{
	int i,j, v;
	for(  i=0 ; i<t->h ; i++ )
	{
		for( j=0 ; j<t->l ; j++ )
		{
			v = nbvois( t, i, j );
			if( v==3 )
				n->cell[i][j] = (t->cell[i][j])?1:2;
			else if( v==2 )
				n->cell[i][j] = (t->cell[i][j])?1:0;
			else
				n->cell[i][j] = 0;
		}
	}
	n->l = t->l;
	n->h = t->h;
}

void affiche( struct tab *t )
{
	int i,j,k;
	cleargraph();
	for( i=0 ; i<t->h ; i++ )
	{
		for( j=0 ; j<t->l ; j++ )
		{
			if( t->cell[i][j]==1 )
			{
				for( k=0 ; k<CARRE ; ++k )
					line(i*(CARRE+INTER)+k,j*(CARRE+INTER),
					     i*(CARRE+INTER)+k,j*(CARRE+INTER)+CARRE-1);
			}
			else if( t->cell[i][j]==2 )
			{
				/* putpixel(i,j); */
				line(i*(CARRE+INTER),j*(CARRE+INTER),
				     i*(CARRE+INTER)+CARRE,j*(CARRE+INTER));
				line(i*(CARRE+INTER)+CARRE,j*(CARRE+INTER),
				     i*(CARRE+INTER)+CARRE,j*(CARRE+INTER)+CARRE);
				line(i*(CARRE+INTER)+CARRE,j*(CARRE+INTER)+CARRE,
				     i*(CARRE+INTER),j*(CARRE+INTER)+CARRE);
				line(i*(CARRE+INTER),j*(CARRE+INTER)+CARRE,
				     i*(CARRE+INTER),j*(CARRE+INTER));
			}

		}
	}
	refresh();
/* 	usleep(100000); */
}


