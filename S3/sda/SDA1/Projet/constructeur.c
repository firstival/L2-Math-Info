/** \file
 * \author Thomas Kuntz
 * Constructeur : Source
 * */

#include "constructeur.h"

int taillePixel(int h,int l)
{
    int i=1;
    while(((i+1)*h<=800) && ((i+1)*l<=1000))i++;
    return i;
}

Matrice debut_generation(Matrice m)
{
    //Création des pointeurs et variables
    Ens e_mur=NULL,e_mur_constructible=NULL,e_mur_externe=NULL;
    Couple c;
    e_mur_externe=EnsAlloc();
    long noir,rouge;

    //initialisation de l'affichage s'il est activé
    if(affichage_generation==1)
    {
        initgraph(TAILLE_PIXEL*m->l,TAILLE_PIXEL*m->h);
		noir=newcolor(0,0,0);
		rouge=newcolor(1,0,0);
        cleargraph();
    }
    //Création des murs autours de la matrice
	e_mur_externe=emmurement(m,e_mur_externe);
	//Initialisation des ensembles de graines,puis de mur constructeurs
    e_mur=initEns_seed(m);
    e_mur_constructible=initEns_murConstructible(e_mur,m);

    if(affichage_generation==1)
    {
        //affichage des murs externes, des graines, et si "-d", des murs constructibles
		DessineEns(e_mur_externe,noir);
		DessineEns(e_mur,noir);
		if(affichage_cases_constructibles==1) DessineEns(e_mur_constructible,rouge);
		refresh();
	}
    //tant qu'il reste des éléments constructibles
    while(e_mur_constructible->taille > 0)
    {
        //on tire un couple(et le supprime de l'ensemble)
        c=EnsTirage(e_mur_constructible);
        //on construit le mur tiré
        m->tab[c.x][c.y]=True;

        //on supprime les 2 murs a coté, et les trois en face du mur nouvellement construit, pour éviter des interactions négatives, si "-d", on efface aussi ces murs
		e_mur_constructible=SupprMurPlusConstructible(c,e_mur_constructible,m);
		//on teste et ajoute si constructible,les 3 murs adjacents au mur construit (ne prend pas en compte la graine), et si "-d", on affiche les nouveaux mur constructibles en rouge
		e_mur_constructible=AjoutNouveauxMursConstructibles(c,e_mur_constructible,m,rouge);


        if(affichage_generation==1)
        {
            //affichage du nouveau mur, en noir
            DessineCouple(c,noir);
            refresh();
        }

    }

    //Désallocation de tout les ensembles, et fermeture de l'affichage graphique
    EnsFree(e_mur);
    EnsFree(e_mur_constructible);
	EnsFree(e_mur_externe);
	if(affichage_generation == 1)
	{
		waitgraph();
		closegraph();
	}
	return m;
}


Couple recherche_seed_mur_constructible(Matrice m,Couple c)
{
    Couple graine={0,0};
    //Si les coordonnées sont bien dans la matrice
    if((m->l-c.x>0)&&(m->h-c.y>0))
    {
            //je teste toutes les cases adjacents, comme il n'y a qu'une graine (car la case est constructible), à la fin, graine a les coordonnées du mur responsable de c
            if((m->tab[c.x-1][c.y])==True)
            {
                graine.x=c.x-1;
                graine.y=c.y;
            }
            if((m->tab[c.x][c.y-1])==True)
            {
                graine.x=c.x;
                graine.y=c.y-1;
            }
            if((m->tab[c.x+1][c.y])==True)
            {
                graine.x=c.x+1;
                graine.y=c.y;
            }
            if((m->tab[c.x][c.y+1])==True)
            {
                graine.x=c.x;
                graine.y=c.y+1;
            }
	}
	return graine;
}



Ens emmurement(Matrice m,Ens e)
{
    int i=0;
    for(i=0;i<m->l;i++)
    {
        m->tab[i][0]=True;
        e=EnsAjoute(e,construCouple(i,0));
        m->tab[i][m->h-1]=True;
        e=EnsAjoute(e,construCouple(i,m->h-1));
    }
    for(i=0;i<m->h;i++)
    {
        m->tab[0][i]=True;
        e=EnsAjoute(e,construCouple(0,i));
        m->tab[m->l-1][i]=True;
        e=EnsAjoute(e,construCouple(m->l-1,i));
    }
    return e;
}

int EstConstructible(Matrice m,Couple c)
{
    int compteur_mur_utiles=0;
    Couple graine={0,0};
    //Si la case est bien dans la matrice
    if(((m->l>c.x)&&(c.x>=0))&&((m->h>c.y)&&(c.y>=0)))
    {
        //si la case n'est pas déjà un mur
        if(m->tab[c.x][c.y] != True)
        {
            //On teste chaque mur adjacents, compteur_mur_utiles est incrémenté si on en trouve un, et graine représente les coordonnées du derniers mur adjacents trouvé
            if((m->tab[c.x-1][c.y])==True)
            {
                compteur_mur_utiles++;
                graine.x=c.x-1;
                graine.y=c.y;
            }
            if((m->tab[c.x][c.y-1])==True)
            {
                compteur_mur_utiles++;
                graine.x=c.x;
                graine.y=c.y-1;
            }
            if((m->tab[c.x+1][c.y])==True)
            {
                compteur_mur_utiles++;
                graine.x=c.x+1;
                graine.y=c.y;
            }
            if((m->tab[c.x][c.y+1])==True)
            {
                compteur_mur_utiles++;
                graine.x=c.x;
                graine.y=c.y+1;
            }
            //Pour être constructible, une case ne doit avoir au moins qu'un seul mur adjacent à ses coté, si ce n'est pas le cas, elle n'est pas constructible
            if(compteur_mur_utiles == 1)
            {
                //diff : vecteur directeur pour aller devant la case testé
                Couple diff={c.x-graine.x,c.y-graine.y};
                //inverse_diff : vecteur directeur pour aller à gauche/droite (selon si on le rend négatif ou non) de la case à tester
                Couple inverse_diff={diff.y,diff.x};
                //Pour être constructible, une case doit aussi avoir les cases devant gauche et devant droite libre, si on en trouve une, alors on incrémente le compteur
                if(m->tab[c.x+diff.x+inverse_diff.x][c.y+diff.y+inverse_diff.y]==True) compteur_mur_utiles++;
                if(m->tab[c.x+diff.x-inverse_diff.x][c.y+diff.y-inverse_diff.y]==True) compteur_mur_utiles++;
            }
        }
    }
    //Si on a trouvé plus d'un murs adjacents à ses cotés ET devant gauche/droite, alors la case n'est pas constructible
    return (compteur_mur_utiles == 1);
}


Ens initEns_seed(Matrice m)
{
	Ens e=NULL;
	e=EnsAlloc();
	//Calcul pour avoir un nombre de graine proportionnel à la taille de la matrice
	int nbSeedH=(m->h -2)/INTER+1;
	int nbSeedL=(m->l -2)/INTER+1;
	int i=0,x,y;
	Couple c;
	int emplacementSeedMur=0;

    //placement des graines sur les murs externes haut et bas
	for(i=0;i < nbSeedL ;i++)
	{
	    //tirage aléatoire d'un abscisse
		emplacementSeedMur=(rand() % (m->l-2)) + 1;
		//si les coordonnées tirées sont déjà ceux d'un mur, on décrémente le compteur du for
		if(EstConstructible(m,construCouple(emplacementSeedMur,1)) == 0) i--;
		//sinon on l'ajoute à l'ensemble de graine, et on le construit sur la matrice
		else
		{
			EnsAjoute(e,construCouple(emplacementSeedMur,1));
			m->tab[emplacementSeedMur][1]=True;
		}

		emplacementSeedMur=(rand() % (m->l-2)) + 1;
		if(EstConstructible(m,construCouple(emplacementSeedMur,m->h-2))== 0) i--;
		else
		{
			EnsAjoute(e,construCouple(emplacementSeedMur,m->h-2));
			m->tab[emplacementSeedMur][m->h-2]=True;
		}
	}
    //placement des graines sur les murs externes de droit et gauche
	for(i=0;i < nbSeedH;i++)
	{
		emplacementSeedMur=(rand() % (m->h-2)) + 1;
		if((EstConstructible(m,construCouple(1,emplacementSeedMur))) == 0) i--;
		else
		{
			EnsAjoute(e,construCouple(1,emplacementSeedMur));
			m->tab[1][emplacementSeedMur]=True;
		}

		emplacementSeedMur=(rand() % (m->l-2)) + 1;
		if((EstConstructible(m,construCouple(m->l-2,emplacementSeedMur))) == 0) i--;
		else
		{
			EnsAjoute(e,construCouple(m->l-2,emplacementSeedMur));
			m->tab[m->l-2][emplacementSeedMur]=True;
		}
	}
    //la fin de la boucle for est calculé proportionnellement, pour avoir un nombre de graine au centre proportionnelle à la taille de la matrice
	for(i=0; i<((2*(nbSeedH + nbSeedL))/4) ; i++)
	{
	    //deux rand pour l'abscisse et l'ordonné de la graine du centre
	    x=(rand() % (m->l-6)) + 3;
	    y=(rand() % (m->h-6)) + 3;
        c=construCouple(x,y);
        //si x,y sont les coordonnées d'un mur, on décrémente i et recommence
	    if(m->tab[c.x][c.y] == True) i--;
	    //sinon on construit et ajoute le mur à l'ensemble des graines
	    else
	    {
	        EnsAjoute(e,c);
	        m->tab[x][y]=True;
	    }

	}

	return e;
}

Ens initEns_murConstructible(Ens e,Matrice m)
{
	Ens em=NULL;
	Couple c,tmp;
    //allocation de l'ensemble des murs contructibles
	em=EnsAlloc();
	if(em != NULL)
	{
	int i=0;
	//Pour tout les éléments de l'ensemble des graines, on testes toutes les cases adjacentes, si elles sont constructibles, on les ajoute à l'ensemble des murs constructibles
	for(i=0;i < (e->taille);i++)
		{
			c=e->tab[i];
			tmp=construCouple(c.x-1,c.y);
			if(EstConstructible(m,tmp) == 1) EnsAjoute(em,tmp);
			tmp=construCouple(c.x,c.y+1);
			if(EstConstructible(m,tmp) == 1) EnsAjoute(em,tmp);
			tmp=construCouple(c.x,c.y-1);
			if(EstConstructible(m,tmp) == 1) EnsAjoute(em,tmp);
			tmp=construCouple(c.x+1,c.y);
			if(EstConstructible(m,tmp) == 1) EnsAjoute(em,tmp);
		}
	}
	return em;
}

Ens SupprMurPlusConstructible(Couple c,Ens emc,Matrice m)
{
	Couple diff,graine;
	graine=recherche_seed_mur_constructible(m,c);
	diff=construCouple(c.x-graine.x,c.y-graine.y);
    //Supprime les deux cases à gauche et droite du "c" et les trois devant de l'ensemble de mur constructibles
	EnsSuppr(emc,construCouple(c.x+diff.x+diff.y,c.y+diff.y+diff.x));
	EnsSuppr(emc,construCouple(c.x+diff.x-diff.y,c.y+diff.y-diff.x));
	EnsSuppr(emc,construCouple(c.x+diff.x,c.y+diff.y));
	EnsSuppr(emc,construCouple(c.x+diff.y,c.y+diff.x));
	EnsSuppr(emc,construCouple(c.x-diff.y,c.y-diff.x));
	if(affichage_cases_constructibles==1)
	{
	    //Si l'affichage est activé, on les efface de l'affichage(Cad, les dessiner en blanc)
		EffaceCouple(construCouple(c.x+diff.x+diff.y,c.y+diff.y+diff.x));
		EffaceCouple(construCouple(c.x+diff.x-diff.y,c.y+diff.y-diff.x));
		EffaceCouple(construCouple(c.x+diff.x,c.y+diff.y));
		EffaceCouple(construCouple(c.x+diff.y,c.y+diff.x));
		EffaceCouple(construCouple(c.x-diff.y,c.y-diff.x));
	}
	return emc;
}


Ens AjoutNouveauxMursConstructibles(Couple c,Ens emc,Matrice m,long couleur)
{
	Couple c1;
    //on teste si les 4 murs adjacents sont constructibles(la graine lié à "c" sera exclue par EstConstructible, car c'est déjà un mur), si oui on les ajoutes à l'ensemble de mur constructibles et les dessines dans la couleur indiquée(si l'affichage est activé)
	c1=construCouple(c.x,c.y+1);
	if(EstConstructible(m,c1) == 1)
	{
		emc=EnsAjoute(emc,c1);
		if(affichage_cases_constructibles ==1) DessineCouple(c1,couleur);
	}

	c1=construCouple(c.x,c.y-1);
	if(EstConstructible(m,c1) == 1)
	{
		emc=EnsAjoute(emc,c1);
		if(affichage_cases_constructibles ==1) DessineCouple(c1,couleur);
	}

	c1=construCouple(c.x+1,c.y);
	if(EstConstructible(m,c1) == 1)
	{
		emc=EnsAjoute(emc,c1);
		if(affichage_cases_constructibles ==1) DessineCouple(c1,couleur);
	}
	c1=construCouple(c.x-1,c.y);
	if(EstConstructible(m,c1) == 1)
	{
		emc=EnsAjoute(emc,c1);
		if(affichage_cases_constructibles ==1) DessineCouple(c1,couleur);
	}

	return emc;
}

void DessineEns(Ens e,long couleur)
{
	int i=0;
	for(i=0;i<e->taille;i++) DessineCouple(e->tab[i],couleur);
}

void DessineCouple(Couple c,long couleur)
{
	setcolor(couleur);
	int k=0;
	for(k=0;k<(TAILLE_PIXEL);++k) line(c.x*TAILLE_PIXEL,c.y*TAILLE_PIXEL+k,c.x*TAILLE_PIXEL + TAILLE_PIXEL -1,c.y*TAILLE_PIXEL+k);
}

void EffaceCouple(Couple c)
{
	DessineCouple(c,newcolor(1,1,1));
}

void EffaceEns(Ens e)
{
	DessineEns(e,newcolor(1,1,1));
}
