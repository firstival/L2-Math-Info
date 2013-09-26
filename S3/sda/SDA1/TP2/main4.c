#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files_chop.h"
#include "sorte.h"


/**fonction qui permet d'afficher le contenu d'une file*/
void FileAffiche(File f)
{
	int i=1;
	while(f.tete != NULL)
	{
		printf("Le %ieme element est : %i\n", i, f.tete->v);
		i++;
		f.tete=f.tete->suivant;
	}
	printf("\n");
}


int main()
{
	File f=FileNouv();
	int stop = 0;
	char input[20];
	char *tok=NULL;


    printf("Veuillez rentrer une commande :\n\tajoute <x> : ajoute l'entier x à la file\n\tsuppr : affiche l'entier en tête de file et le supprime de la file\n\tetat : Affiche \"vide\" ou \"non vide\" selon l'etat de la file, et sa taille si elle n'est pas vide\n\taffiche : affiche le contenu de la file\n\tquit : detruit la file et termine le programme\n\n");

    while(stop !=1)
    {
        int i=0;

        fgets(input,15,stdin);
        while(input[i] != '\n') i++;
        input[i]='\0';

        tok=strtok(input," ");
        if(strcmp("ajoute", input) == 0)
        {
            tok=strtok(NULL, " ");
            S ajoute= atoi(tok);
            f=FileAdjQ(f,ajoute);
        }
        else if(strcmp("suppr",input) == 0)
        {
            printf("L'entier \"%i\" en tete de file a ete supprime\n\n", f.tete->v);
            f=FileSupT(f);
        }
        else if(strcmp("etat", input) == 0)
        {
            if(FileEstVide(f) == 1) printf("La file est vide\n\n");
            else printf("La file est non-vide, sa taille est de %i\n\n", FileTaille(f));
        }
        else if(strcmp("affiche", input) == 0)
        {
            FileAffiche(f);
        }
        else if (strcmp("quit", input) == 0)
        {
            stop =1;
            FileDetruit(f);
        }
        else
        {
            printf("Vous n'avez pas taper une commande valide\n,");
            printf("Veuillez rentrer une commande :\n\tajoute <x> : ajoute l'entier x à la file\n\tsuppr : affiche l'entier en tête de file et le supprime de la file\n\tetat : Affiche \"vide\" ou \"non vide\" selon l'etat de la file, et sa taille si elle n'est pas vide\n\taffiche : affiche le contenu de la file\n\tquit : detruit la file et termine le programme\n\n");

        }
    }

return 0;
}
