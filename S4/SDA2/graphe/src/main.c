#include <stdio.h>
#include <stdlib.h>

#include "graphe_oriente.h"


int main(int argc, char *argv[])
{
	Graphe g=grnouv();
	int i=1;
	for(i=1;i<10;i++) g=adjs(g,i);
	g=adja(g,1,2);
	g=adja(g,1,5);
	g=adja(g,4,1);
	g=adja(g,4,6);
	g=adja(g,7,2);
	g=adja(g,7,9);
	g=adja(g,3,1);
	g=adja(g,3,4);
	g=adja(g,1,7);
	g=adja(g,8,6);
	g=adja(g,9,6);
	g=adja(g,9,3);
	afficheGraphe(g);
	supa(g,3,1);
	afficheGraphe(g);
	printf("Le sommet 12 est dedans? %d, le 4? %d\n",exs(g,12),exs(g,4));
	printf("l'arc (4,1) existe? %d, et (7,9)? %d, et (9,4)? %d\n", exa(g,4,1), exa(g,7,9) , exa(g,9,4) );
	
	printf("Ajout d'un 10eme sommet\n");
	g=adjs(g,10);
	afficheGraphe(g);
	
	printf("Suppression du 10eme sommet, puis du 3eme\n");
	g=sups(g,10);
	afficheGraphe(g);
	g=sups(g,3);
	afficheGraphe(g);
	
	printf("Degré ext de 1 : %d, interieur : %d\n", de(g,1),di(g,1));
	
	for(i=1;i<10;i++) g=sups(g,i);
	
	
	return 0;
}
