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
		if(compteur>N)//Si on a d�pass� le nombre d'it�ration maximum, on desalloue les matrices et sort en affichant un message d'erreur.
		{
			deleteMatrix(a);
			deleteMatrix(valpropre);
			deleteMatrix(resultat);
			fprintf(stderr,"Erreur : Nombre maximum d'it�ration d�pass�\n");
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
		if(compteur>N)//Si on a d�pass� le nombre d'it�ration maximum, on remet une nouvelle matrice al�atoire dans valpropre et on continue de chercher avec celle l�
		{
			freopen(filename,"w",file);//Permet de fermer puis rouvrir le fichier, ce qui �crase le fichier de l'ancienne matrice (vu qu'elle n'a pas abouti)
			valpropre=randomMatrix(valpropre);
			compteur=0;
			i=0;
			
			EcrireMatrice(valpropre,file);//J'�crie la premi�re forme dans le fichier
		}
			

        qr=decompositionQR(valpropre);//Ak=Qk*Rk
        deleteMatrix(valpropre);
        valpropre=multiplication(qr.r,qr.q);//Ak+1=Rk*Qk

        deleteMatrix(qr.r);
        deleteMatrix(qr.q);


        compteur++;
        if(compteur%PAS==0)//toute les PAS ieme matrices, on l'�crit dans le fichiers
        {
			i++;//Ce compteur sert a dir combien de fois on a �crit une matrice dans le fichier
			EcrireMatrice(valpropre,file);
		}
    }
	EcrireMatrice(valpropre,file);//On �crit la forme final de la matrice (vu que si on est la, on a r�ussi a trouver al�atoirement une matrice dont on a trouv� les valeurs propres)
	
	fprintf(file,"%d\n",compteur);//On �crit le nombre d'it�ration, c'est inutile pour la suite, mais pour l'utilisateur, �a peut �tre int�ressant de savoir combient d'it�ration �a a pris
	fprintf(file,"%d\n",valpropre->nb_rows);//On �crit la taille de la matrice dont on a cherch� les valeurs propres
	fprintf(file,"%d",i+2);//On �crit le nombre de fois o� on a �crit la matrice dans le fichier (permet de gerer l'affichage gnuplot plus tard avec le script GenererFichier.sh)
	
    deleteMatrix(valpropre);
    fclose(file);
}
/*
 * Cette fonction n'�crit pas vraiment la matrice dans le fichier, elle �crit plutot les coordonn�es (avec le num�ro de la ligne invers�, pour correspondre � une ordonn� dans un rep�re) des valeurs non nulle de la matrice
 * Cela permet apr�s avec gnuplot d'afficher des crois � l'emplacement (x,y) si � cette endroit, la matrice avait une valeur non nulle.
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
	fprintf(file,"\n\n");//On affiche deux saut de ligne pour s�parer chaque matrice �crite les unes des autres 
	fflush(file);//Je pr�f�re flush le buffer
}
