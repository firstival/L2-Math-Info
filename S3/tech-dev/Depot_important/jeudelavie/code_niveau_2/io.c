#include "io.h"

static int temps = 0;
extern int mode_voisinage;
extern int mode_vieillissement;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ",ligne[i]-1);
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("temps t = %d\n", temps); 
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 6); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				temps ++; 
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' : 
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
			case 'c' :
			{// touche "c" pour activer/désactiver le mode cyclique
				if(mode_voisinage == 0)
				{
					mode_voisinage=1;
					printf("Mode voisinage cyclique active     ");
				}
				else
				{
					mode_voisinage =0;
					printf("Mode voisinage cyclique desactive");
				}
				while(getchar() != '\n');
				printf("\e[1A");
				break;
			}
			case 'v' :
			{// touche "v" pour activer/désactiver le mode vieillissement
				if(mode_vieillissement == 0)
				{
					mode_vieillissement=1;
					printf("Mode vieillissement active     ");
				}
				else
				{
					mode_vieillissement =0;
					printf("Mode vieillissement desactive");
				}
				while(getchar() != '\n');
				printf("\e[1A");
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
