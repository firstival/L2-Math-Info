#include "valeur_propre.h"

int estNulle(double a)
{
    return ((a<EPSILON)&&(a>-EPSILON));
}

int estTriangulaireSup(Matrix a)
{
    int i=0;
    int j=0;
    double tmp;

    for(j=0;j<a->nb_rows;j++)
    {
		for(i=0;i<j;i++)
        {
            tmp=getElt(a,j,i);
            if(!estNulle(tmp)) return 0;
        }
    }
    return 1;
}


int valeurPropre(Matrix a,Matrix * v)
{
    QR_t qr;
    Matrix valpropre=copieMatrix(a);
    Matrix resultat=newMatrix(a->nb_rows,1);//Cet matrice est le vecteur qui va contenir les valeurs propres
    int compteur=0;
    int i=0;

    while((estTriangulaireSup(valpropre))==0)
    {
		if(compteur>N)//Si on a dépassé le nombre d'itération maximum, on desalloue les matrices et sort en affichant un message d'erreur.
		{
			deleteMatrix(a);
			deleteMatrix(valpropre);
			deleteMatrix(resultat);
			fprintf(stderr,"Erreur : Nombre maximum d'itération dépassé\n");
			exit(2);
		}
        qr=decompositionQR(valpropre);//Ak=Qk*Rk
        deleteMatrix(valpropre);
        valpropre=multiplication(qr.r,qr.q);//Ak+1=Rk*Qk

        deleteMatrix(qr.r);
        deleteMatrix(qr.q);

        compteur++;
    }

    for(i=0;i<a->nb_rows;i++) setElt(resultat,i,0,getElt(valpropre,i,i));//On met les valeurs dans le vecteurs
    deleteMatrix(valpropre);
    *v=resultat;
    return compteur;
}


void valeurPropre_gnuplot(Matrix a,char * filename)
{
    FILE * file=fopen(filename,"w");
    QR_t qr;
    Matrix valpropre=copieMatrix(a);
    int compteur=0;
    int i=0;

    EcrireMatrice(valpropre,file);//On ecrit la matrice originel dans le fichier

    while((estTriangulaireSup(valpropre))==0)
    {
		if(compteur>N)//Si on a dépassé le nombre d'itération maximum, on remet une nouvelle matrice aléatoire dans valpropre et on continue de chercher avec celle là
		{
			freopen(filename,"w",file);//Permet de fermer puis rouvrir le fichier, ce qui écrase le fichier de l'ancienne matrice (vu qu'elle n'a pas abouti)
			valpropre=randomMatrix(valpropre);
			compteur=0;
			i=0;
			
			EcrireMatrice(valpropre,file);//J'écrie la première forme dans le fichier
		}
			

        qr=decompositionQR(valpropre);//Ak=Qk*Rk
        deleteMatrix(valpropre);
        valpropre=multiplication(qr.r,qr.q);//Ak+1=Rk*Qk

        deleteMatrix(qr.r);
        deleteMatrix(qr.q);


        compteur++;
        if(compteur%PAS==0)//toute les PAS ieme matrices, on l'écrit dans le fichiers
        {
			i++;//Ce compteur sert a dir combien de fois on a écrit une matrice dans le fichier
			EcrireMatrice(valpropre,file);
		}
    }
	EcrireMatrice(valpropre,file);//On écrit la forme final de la matrice (vu que si on est la, on a réussi a trouver aléatoirement une matrice dont on a trouvé les valeurs propres)
	
	fprintf(file,"%d\n",compteur);//On écrit le nombre d'itération, c'est inutile pour la suite, mais pour l'utilisateur, ça peut être intéressant de savoir combient d'itération ça a pris
	fprintf(file,"%d\n",valpropre->nb_rows);//On écrit la taille de la matrice dont on a cherché les valeurs propres
	fprintf(file,"%d",i+2);//On écrit le nombre de fois où on a écrit la matrice dans le fichier (permet de gerer l'affichage gnuplot plus tard avec le script GenererFichier.sh)
	
    deleteMatrix(valpropre);
    fclose(file);
}
/*
 * Cette fonction n'écrit pas vraiment la matrice dans le fichier, elle écrit plutot les coordonnées (avec le numéro de la ligne inversé, pour correspondre à une ordonné dans un repère) des valeurs non nulle de la matrice
 * Cela permet après avec gnuplot d'afficher des crois à l'emplacement (x,y) si à cette endroit, la matrice avait une valeur non nulle.
 */
void EcrireMatrice(Matrix a,FILE * file)
{
    int i=0;
    int j=0;
    double tmp;
    for(i=0;i<a->nb_rows;i++)
    {
        for(j=0;j<a->nb_columns;j++)
        {
            tmp=getElt(a,i,j);
            if(!estNulle(tmp)) fprintf(file,"%d %d\n",j,a->nb_rows-i-1);
		}
	}
	fprintf(file,"\n\n");//On affiche deux saut de ligne pour séparer chaque matrice écrite les unes des autres 
	fflush(file);//Je préfère flush le buffer
}
