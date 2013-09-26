/** \file
 * \author Thomas Kuntz
 * main de genlab : Source
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ensemble.h"
#include "matrice.h"
#include "constructeur.h"
#include "graph.h"

#define LARGEUR_DEFAULT 300
#define HAUTEUR_DEFAULT 200

int affichage_generation = 0;
int affichage_cases_constructibles = 0;
int TAILLE_PIXEL = 3;

int main(int argc, char ** argv)
{
    //Si l'utilisateur n'a pas mis assez d'argument au programme, on stop la, et donne la description de l'usage du programme
    if(argc<2)
    {
        printf("Usage genlab : ./genlab [-v] [-d] [-l <largeur>] [-h <hauteur>] [-p <taille pixel>] <fichier>\n");
        return 1;
    }

    srand(time(NULL));

    int i=1,l=LARGEUR_DEFAULT,h=HAUTEUR_DEFAULT;
    int lcheck=0,hcheck=0,pcheck=0;



    for(i=1;i<argc-1;i++)
    {
            if(strcmp(argv[i],"-v") == 0)
            {
                affichage_generation=1;//activation de l'affichage
            }
            else if(strcmp(argv[i],"-d") == 0)
            {
                affichage_cases_constructibles=1;//activation de l'affichage des cases constructibles
                affichage_generation=1;
            }
            else if(strcmp(argv[i],"-l") == 0)
            {
                //récuperation de la largeur
                i++;
                l=atoi(argv[i]);
                lcheck=1;
            }
            else if(strcmp(argv[i],"-h") == 0)
            {
                //récupération de la hauteur
                i++;
                h=atoi(argv[i]);
                hcheck=1;
            }
            else if(strcmp(argv[i],"-p") == 0)
            {
                //récupération de la taille de pixel
                i++;
                TAILLE_PIXEL=atoi(argv[i]);
                pcheck=1;
            }
    }
    //si l'utilisateur n'a renseigné qu'une seule des tailles pour le coté de la matrice, on calcule le deuxième non donné proportionnellement à celui donné
    if((lcheck == 0) != (hcheck==0))
       {
           if(lcheck == 1) h=(100*l)/150;
           else l=(150*h)/100;
       }
    //Si on dépasse 1000 en largeur, la largeur est ramenée à 1000
    if(l>1000) l=1000;
    //pareil pour la hauteur
    if(h>800)h=800;
    //Si la taille de pixel n'a pas été donné par l'utilisateur, on la calcule proportionnellement à la taille de la matrice
    if(pcheck==0)TAILLE_PIXEL=taillePixel(h,l);



    Matrice m=NULL;
    m=MatAlloc(h,l);//allocation de la matrice de taille h*l

    if(m == NULL)
    {
        printf("Erreur lors de l'initialisation de la matrice");
        return 1;
    }
    //début de la génération du labyrinthe
    m=debut_generation(m);

    if((MatSauve(m,argv[argc-1])) == 0) return 1;
    MatFree(m);//libération de la matrice
	return 0;
}
