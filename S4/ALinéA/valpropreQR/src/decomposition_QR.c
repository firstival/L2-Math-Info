#include "decomposition_QR.h"

double norme(Matrix x)
{
	double retour=-1;
	int i=0;
	double tmp;
	if(x->nb_columns==1)
	{
		retour=0;
		for(i=0;i<x->nb_rows;i++)
		{
			tmp=getElt(x,i,0);
			retour+=(tmp*tmp);
		}
		retour=sqrt(retour);
	}
	return retour;
}


Matrix MatriceIdentite(int n)
{
    Matrix id=newMatrix(n,n);
    int i=0;
    for(i=0;i<n;i++) setElt(id,i,i,1);
    return id;
}

void remiseSousFormeIdentie(Matrix a)
{
    int i=0;
    int j=0;
    for(i=0;i<a->nb_columns;i++)
    {
        for(j=0;j<a->nb_rows;j++)
        {
            if(i==j) setElt(a,i,i,1);
            else setElt(a,j,i,0);
        }
    }
}

Matrix ExtractionMatrix(Matrix A,int nc,int nl,int i,int j)
{
	//Si la matrice a extraire est trop grande, on baisse la taille a extraire
    if(nc+i>A->nb_columns) nc=A->nb_columns-i;
    if(nl+j>A->nb_rows) nl=A->nb_rows-j;

    Matrix tmp=newMatrix(nl,nc);
    int a=0;
    int b=0;
    for(a=0;a<nc;a++)
    {
        for(b=0;b<nl;b++)
        {
            setElt(tmp,b,a,getElt(A,b+j,a+i));
        }
    }
    return tmp;
}

void insertionMatriceDansMatrice(Matrix A,Matrix B,int i,int j)
{
    int a=0;
    int b=0;

    for(a=0 ; a< B->nb_columns;a++)
    {
        for(b=0 ; b< B->nb_rows;b++)
        {
            setElt(A,b+j,a+i,getElt(B,b,a));
        }
    }
}


Matrix extract_vectorX(Matrix A)
{
    Matrix X=newMatrix(A->nb_rows,1);
    int i=0;
    for(i=0;i<X->nb_rows;i++)
    {
        setElt(X,i,0,getElt(A,i,0));
    }
    return X;
}

E alpha(Matrix x)
{
	double n=norme(x);
	double tmp=getElt(x,0,0);
	if(n == -1)
	{
		fprintf(stderr,"Erreur : la matrice x n'est pas un vecteur");
		exit(2);
	}
	if(!((tmp<0 && n<0)||(tmp>0 && n>0))) n=-n;
	return n;
}


Matrix vecteurU(Matrix x)
{
	double a=alpha(x);
	int i=0;
	Matrix vecteurA=newMatrix(x->nb_rows,1);
	
	for(i=0;i<x->nb_rows;i++)setElt(vecteurA,i,0,getElt(x,i,0));//On extrait la 1er colonne de x
	
	setElt(vecteurA,0,0,getElt(vecteurA,0,0)-a);//U=x-alpha*(1,0,....,0)
	return vecteurA;
}


Matrix vecteurV(Matrix u)
{
	int i=0;
	Matrix v=copieMatrix(u);
	double n=norme(u);
	for(i=0;i<u->nb_rows;i++) setElt(v,i,0,getElt(u,i,0)/n);//V=U/norme(U)
	return v;
}


Matrix Matrice_Q_aux(Matrix v)//On créer la matrice Q=Id-2V*Vt, avec Vt la transposé de V
{
    Matrix v_t=transpose(v);
    Matrix tmp1=multiplication(v,v_t);
    Matrix identite=MatriceIdentite(tmp1->nb_rows);
    Matrix tmp2=mult_scalar(2,tmp1);
    Matrix Q=soustraction(identite,tmp2);

    deleteMatrix(identite);
    deleteMatrix(v_t);
    deleteMatrix(tmp1);
    deleteMatrix(tmp2);

    return Q;
}


Matrix Matrice_Qk(Matrix A)//On créer la matrice Qk de householder a partir de A
{
    Matrix X=extract_vectorX(A);
    Matrix U=vecteurU(X);
    Matrix V=vecteurV(U);

    Matrix Q=Matrice_Q_aux(V);
    deleteMatrix(X);
    deleteMatrix(U);
    deleteMatrix(V);

    return Q;
}


QR_t decompositionQR(Matrix a)
{
    Matrix R=copieMatrix(a);
    Matrix Q_t=MatriceIdentite(a->nb_columns);//Q^t, la transposé de la matrice Q, on met l'identité dedans pour pouvoir faire Qk+1 * Qk, avec k=0,Qk=Id
    Matrix Q=NULL;

    Matrix Qk=NULL;
    Matrix tmp1=NULL;
    Matrix tmp2=NULL;

    Matrix A_prime=NULL;
    Matrix id=newMatrix(a->nb_rows,a->nb_columns);

    int i=0;
    for(i=0;i < (a->nb_rows-1); i++)
    {
        A_prime=ExtractionMatrix(R,R->nb_columns-i,R->nb_columns-i,i,i);//On extrait la sous matrice de R sur laquel on va chercher Qk
        Qk=Matrice_Qk(A_prime);//On cherche Qk'
        deleteMatrix(A_prime);

        remiseSousFormeIdentie(id);//On remet id sous sa forme d'identité
        insertionMatriceDansMatrice(id,Qk,i,i);//On insère Qk' dans id (comme wikipedia dit : avec des 1 au dessus a gauche de Qk, et des 0 sur les lignes et colonnes), ce qui donne Qk
        deleteMatrix(Qk);
        tmp1=id;

        tmp2=multiplication(tmp1,R);//R=Qk*R
        deleteMatrix(R);
        R=tmp2;

        tmp2=multiplication(tmp1,Q_t);//Q_t=Qk*Q_t
        deleteMatrix(Q_t);
        Q_t=tmp2;
    }

    Q=transpose(Q_t);//Au final on transpose Q_t pour avec Q
    QR_t resultat={Q,R};//R a été construit avant itérativement, pas besoin de faire un quelconque traitement suplémentaire


    deleteMatrix(Q_t);
    deleteMatrix(id);

    return resultat;
}

