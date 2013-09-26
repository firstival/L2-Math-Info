/** \file
 * \author Thomas Kuntz
 * main de cheminlab : Source
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "matrice.h"
#include "solveur.h"

int affichage = 0;
int TAILLE_PIXEL = 3;

int main(int argc, char ** argv)
{
    //initialisation du rand()
	srand(time(NULL));

    int pcheck=0,i=0;
    Matrice m;
    //Si il n'y a pas assez d'argument, on termine et renvoie la description de l'usage du progamme
    if(argc<2)
    {
        printf("Usage cheminlab : ./cheminlab [-v] [-p <taille pixel>] <fichier labyrinthe>\n");
        return 1;
    }

    for(i=1;i<argc-1;i++)
    {
        if(strcmp(argv[i],"-v") == 0)
        {
            affichage=1;//activation de l'affichage
        }
        else if(strcmp(argv[i],"-p") == 0)
        {
            i++;
            TAILLE_PIXEL=atoi(argv[i]);//définition manuel de l'utilisateur de la taille de pixel
            pcheck=1;
        }
    }
    m=MatLit(argv[argc-1]);
    //si l'utilisateur n'a pas données de taille de pixel, on la calcul pour qu'elle soit acceptable pour l'écran
    if(pcheck==0)TAILLE_PIXEL=taillePixel(m->h,m->l);
    //début de la recherche de chemin
    debut_recherche_naif(m);

	return 0;
}
