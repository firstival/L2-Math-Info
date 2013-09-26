#include "jeu.h"
//mode cyclique activé(=1) par défaut
int mode_voisinage = 1;
//mode calcul du vieillissement désactivé(=0) par défaut
int mode_vieillissement = 0;

//tableaux de fonctions qui gèreront le changement de mode de voisinage
fct_vivant fct_voisin[2]={compte_voisins_vivants_non_cyclique,compte_voisins_vivants_cyclique};
fct_vivant fct_est_vivant[2]={est_vivante_non_cyclique,est_vivante};

//tableaux de fonctions qui gèreront le vieillissement et l'immortalitée des cellules
fct_vieillesse test_execution[2]={test_immortelle,test_vieillesse};
fct_vivre vivre[2]={set_vivante,vieillir};


int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int v = 0;
	v+= est_vivante_non_cyclique(i-1,j-1,g);
	v+= est_vivante_non_cyclique(i-1,j,g);
	v+= est_vivante_non_cyclique(i-1,j+1,g);
	v+= est_vivante_non_cyclique(i,j-1,g);
	v+= est_vivante_non_cyclique(i,j+1,g);
	v+= est_vivante_non_cyclique(i+1,j-1,g);
	v+= est_vivante_non_cyclique(i+1,j,g);
	v+= est_vivante_non_cyclique(i+1,j+1,g);

	return v; 
}

int test_vieillesse(int v,int x,int y,grille g)
{
	return (v!=2 && v!= 3) || (g.cellules[x][y]>8);
}

int test_immortelle(int v,int x,int y,grille g)
{
	return (v!=3 && v!=2);
}

void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = fct_voisin[mode_voisinage](i, j, *gc);
			if (fct_est_vivant[mode_voisinage](i,j,*g)) 
			{ // evolution d'une cellule vivante
				if (test_execution[mode_vieillissement](v,i,j,*gc)) set_morte(i,j,*g);
				else vivre[mode_vieillissement](i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
