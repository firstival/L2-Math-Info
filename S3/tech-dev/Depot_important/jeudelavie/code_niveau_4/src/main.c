#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

int main (int argc, char ** argv) {
	grille g, gc;
	init_grille_from_file("../donnees/grille3.txt",&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	debut_jeu_cairo(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
