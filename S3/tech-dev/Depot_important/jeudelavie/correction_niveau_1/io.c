#include "io.h"

static int temps = 0; // TODO : à ajouter

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("temps t = %d\n", temps); // TODO : à programmer
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 6); // TODO : à modifier
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				temps ++; // TODO : à programmer
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' : // TODO : à programmer
			{ // touche "n" pour nouvelle grille
				libere_grille(g);
				libere_grille(gc);
				temps = 0;
				char name [128];
				printf("nom du fichier à charger :\n");
				scanf("%s", name);
				init_grille_from_file(name,g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g);
				while(getchar() != '\n');
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
