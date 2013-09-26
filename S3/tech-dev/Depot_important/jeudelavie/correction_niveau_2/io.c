#include "io.h"

extern int (*compte_voisins_vivants) (int, int, grille); // TODO : à ajouter
extern void (*set_continue_vie) (int, int, grille); // TODO : à ajouter
static int temps = 0; 

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ",ligne[i]); // TODO : a modifier
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
			case 'c' : // TODO : à programmer
			{ // touche "c" pour activer / desactiver le voisinage cyclique
				if (compte_voisins_vivants == compte_voisins_cyclique){
					compte_voisins_vivants = compte_voisins_non_cyclique;
					printf("voisinage non cyclique    \n");
				}
				else {
					compte_voisins_vivants = compte_voisins_cyclique;
					printf("voisinage cyclique      \n");
				}
				
				while(getchar() != '\n');
				printf("\n\e[%dA",3); 
				break;
			}
			case 'v' : // TODO : à programmer
			{ // touche "v" pour activer/desactiver le viellissement des cellules
				if (set_continue_vie == set_ne_viellit_pas){
					set_continue_vie = set_viellit;
					printf("viellissement ON     \n");
				}
				else {
					set_continue_vie = set_ne_viellit_pas;
					printf("viellissement OFF    \n");
				}
				while(getchar() != '\n');
				printf("\n\e[%dA",3); 
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
