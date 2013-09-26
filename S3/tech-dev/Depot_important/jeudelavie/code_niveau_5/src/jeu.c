#include "jeu.h"

int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_non_cyclique ; 
void (*set_continue_vie)(int,int,grille) = set_ne_viellit_pas ; 

int compte_voisins_cyclique (int i, int j, grille g){
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

int compte_voisins_non_cyclique (int i, int j, grille g){ 
	int v = 0, l=g.nbl, c = g.nbc;
	if (i>0) { // voisins à gauche
		if ( j > 0 ) v+= est_vivante(i-1,j-1,g);
		v+= est_vivante(i-1,j,g);
		if ( j < c-1) v+= est_vivante(i-1,j+1,g);
	}

	// voisins haut et bas
	if ( j > 0 ) v+= est_vivante(i,j-1,g);
	if ( j < c-1) v+= est_vivante(i,j+1,g);

	if (i < l-1 ) { // voisins à droite
		if ( j > 0 ) v+= est_vivante(i+1,j-1,g);
		v+= est_vivante(i+1,j,g);
		if ( j < c-1) v+= est_vivante(i+1,j+1,g);
	}
	
	return v; 
}


void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (est_viable(i,j,*g)){ 
				v = compte_voisins_vivants (i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
					else set_continue_vie(i,j,*g); 
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 ) set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}
//Compare deux grille sans tenir compte de l'age des celulles
int compare_grille_general(grille g1,grille g2)
{
	int resultat=1;
	if((g1.nbc != g2.nbc) || (g1.nbl != g2.nbl)) resultat=0;
		int i=0,j=0;
	for(i=0;(i<g1.nbl) && (resultat==1);i++)
	{
		for(j=0;(j<g1.nbc) && (resultat==1);j++)
		{
			if (!((est_vivante(i,j,g1) && est_vivante(i,j,g2)) || (g1.cellules[i][j]==0 && g2.cellules[i][j]==0) || (!est_viable(i,j,g1) && !est_viable(i,j,g2)))) resultat=0;
		}
	}

	return resultat;
}

//Compare deux grille avec prise en compte de l'age des cellules
int compare_grille_age(grille g1,grille g2)
{
	int resultat=1;
	if((g1.nbc != g2.nbc) || (g1.nbl != g2.nbl)) resultat=0;
		int i=0,j=0;
	for(i=0;(i<g1.nbl) && (resultat==1);i++)
	{
		for(j=0;(j<g1.nbc) && (resultat==1);j++)
		{
			if((g1.cellules[i][j]) != (g2.cellules[i][j])) resultat=0;
		}
	}

	return resultat;
}
//Teste si il reste encore des cellules vivantes dans la grille
int test_grille_encore_vivante(grille g)
{
	int i=0,j=0;
	int resultat=0;
	for(i=0;(i<g.nbl) && (resultat==0);i++)
	{
		for(j=0;(j<g.nbc) && (resultat==0);j++)
		{
			if((g.cellules[i][j]) > 0) resultat=1;
		}
	}
	
	return resultat;
}

/*On crée une grille temporaire qu'on initialise au même état que g, et on la fait evoluer en boucle, à chaque fois, on la compare à la grille initial g
avec les fonctions qui tiennent et ne tiennent pas compte de l'age. 
*/
int test_oscillante(grille * g,grille * gc)
{
	int resultat1=0,resultat2=0,resultatfinal=0,stop1=1,stop2=1,i=0;
	int max=100;
	grille gtmp;
	grille gtest;
	
	alloue_grille(g->nbl,g->nbc,&gtmp);
	copie_grille(*g,gtmp);
	
	alloue_grille(g->nbl,g->nbc,&gtest);
	copie_grille(*g,gtest);
	
	
	
	while((resultat1<max) && stop1)
	{
		evolue(&gtmp,gc);
		resultat1++;
		if(compare_grille_general(*g,gtmp)==1) stop1=0;
	}
	//Si on est arrivé à la fin, mais qu'on a pas trouvé de periode, le resultat vaux -1, sinon, on a donc trouvé un periode
	if((resultat1==max) && (!compare_grille_general(gtmp,*g))) resultat1=-1;
	else
	{
		copie_grille(gtmp,gtest);
		for(i=0;i<resultat1;i++) evolue(&gtest,gc);//Avec la periode trouvé, on initialise au grille au temps T0 + periode, et on la fait evoluer periode fois
		
		if(compare_grille_age(gtmp,gtest)==0) resultat1=-1;//On compare la grille à T0 + periode, et T0 + 2*periode : ce teste permet de distinguer les grilles perdants régulièrements de la vie (et donc une grille voué à la mort,donc non oscillante) et les grilles oscillante
															//Car dans le while en haut, la fonction compare_grille_general, ne peux pas faire la différence, car le seul moyen de voir s'il y a des pertes de vie, c'est d'avoir un "pseudo-periode"
	}
	

	copie_grille(*g,gtmp);
	while((resultat2<max) && stop2)
	{
		evolue(&gtmp,gc);

		resultat2++;
		if(compare_grille_age(*g,gtmp)==1) stop2=0;
	}
	if((resultat2==max) && (!compare_grille_general(gtmp,*g))) resultat2=-1;
	
	//Affection du resultat final en fonction des resultats obtenus par les différentes fonctions de comparaison, si comparaison_grille_age conduit à la trouvaille d'une periode, il a la priorité, sinon c'est l'autre
	if(resultat2 != -1) resultatfinal=resultat2;
	else resultatfinal=resultat1;
	
	
	libere_grille(&gtmp);
	libere_grille(&gtest);
	return resultatfinal;
}

Couple test_oscillation_delai(grille * g,grille * gc)
{
	int max = 100,i=0,tmp,stop=1;
	Couple resultat={-1,-1};
	grille gtest;
	
	alloue_grille(g->nbl,g->nbc,&gtest);
	copie_grille(*g,gtest);
	
	//Simple boucle qui fait evoluer une grille tampon (en incrémentant un compteur) et qui l'envoie à test_oscillation, et s'il trouve une periode, on renvoie un couple contenant le delai et la periode
	
	while((i<max) && stop)
	{
		if(test_grille_encore_vivante(gtest))
		{
			tmp=test_oscillante(&gtest,gc);
			if(tmp != -1)
			{
				resultat=construCouple(i,tmp);
				stop=0;
			}
		}
		else
		{
			stop=0;
			resultat=construCouple(i,0);
		}
		
		evolue(&gtest,gc);
		i++;
	}
	
	libere_grille(&gtest);
	return resultat;
}
