/** \file
 * \author Thomas Kuntz
 * Matrice : Source
 * */

#include "matrice.h"

Matrice MatAlloc(int h,int l)
{
    int i=0,j=0;

    Matrice m=NULL;
    m=(Matrice)malloc(sizeof(StrMatrice));
    m->h=h;
    m->l=l;
    m->tab=(Bool **)malloc(l * (sizeof(Bool *)));

    for(i=0;i<l;i++)
    {
        m->tab[i]=(Bool *)malloc(h * (sizeof(Bool)));
    }

    for(i=0;i<l;i++)
    {
        for(j=0;j<h;j++)
        {
            m->tab[i][j]=False;
        }
    }

    return m;
}

void MatFree(Matrice m)
{
    int i;
    for(i=0;i < (m->l);i++)
    {
        free(m->tab[i]);
    }
    free(m->tab);
    free(m);
}

Bool MatVal(Matrice m,Couple c)
{
    return m->tab[c.x][c.y];
}


Matrice MatSet(Matrice m,Couple c,Bool val)
{
    m->tab[c.x][c.y]=val;
    return m;
}

int CompteTrue(Matrice m)
{
    int i,j,compteur=0;
    for(j=0;j<m->h;j++)
    {
        for(i=0;i<m->l;i++)
        {
            if(m->tab[i][j]==True)compteur++;
        }
    }
    return compteur;
}

int MatSauve(Matrice m,char * nom_fichier)
{
    FILE * pfile=NULL;
    pfile=fopen(nom_fichier,"w");
    if(pfile != NULL)
    {
        //Ecrit dans le fichier la hauteur et largeur
        fprintf(pfile, "%d %d\n",m->h, m->l);
        //Ecrit le nombre total de mur de m
        fprintf(pfile, "%d\n",CompteTrue(m));

        int i,j;
        for(j=0;j<m->h;j++)
        {
            for(i=0;i<m->l;i++)
            {
                if(m->tab[i][j]==True)fprintf(pfile,"%d %d\n",i,j);//Parcourir toute la matrice, si on tombe sur un mur, on ecrit les coordonnées du mur dans le fichier
            }
        }
        fputc('\n',pfile);
        fclose(pfile);

    }
    else
    {
        printf("Erreur dans l'ouverture du fichier pour la sauvegarde");
        return 0;
    }
    return 1;
}


Matrice MatLit(char * nom_fichier)
{
    FILE * pfile=NULL;
    Matrice m=NULL;
    pfile=fopen(nom_fichier,"r");
    if(pfile !=NULL)
    {
        int i,j=0;
        int x,y;
        fscanf(pfile,"%d",&y);//lecture de la hauteur
        fscanf(pfile,"%d",&x);//lecture de la largeur
        fscanf(pfile,"%d", &i);//lecture du nombre de mur total de la matrice

        m=MatAlloc(y,x);//Allocation de la matrice h*l

        for(j=0;j<i;j++)
        {
            fscanf(pfile,"%d",&x);//lecture de l'abscisse
            fscanf(pfile,"%d",&y);//lecture de l'ordonné
            m->tab[x][y]=True;//construction du mur de coordonnée (x,y)
        }
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier pour la lecture");
    }
    return m;
}

