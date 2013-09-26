/** \file
 * \author Thomas Kuntz
 * Solveur : Source
 * */

#include "solveur.h"

int taillePixel(int h,int l)
{
    int i=1;
    while(((i+1)*h<=800) && ((i+1)*l<=1000))i++;
    return i;
}


Matrice debut_recherche_naif(Matrice m)
{
    //Création des variables de couleurs, les couples, et les pointeurs
    Ens dejavu=NULL,parcours=NULL;
    Couple tmp,debut={1,1},fin={m->l-2,m->h-2},pas,positionActuelle,positionFuture;
    long noir,bleu,gris;

    //Allocation de l'ensemble des cases déjà visitées
    dejavu=EnsAlloc();
    //Allocation de l'ensemble (avec notion d'ordre) qui représente le parcours de l'aglo (donc la liste des coordonnées des cases par lequels l'algo est passé depuis le début
    parcours=EnsAlloc();

    //on ajoute la position initial dans l'ensemble des cases déjà vu, ainsi que dans le parcours
    EnsAjoute(dejavu,debut);
    EnsAjoute(parcours,debut);

    if(affichage==1)
    {
        //Création des couleurs, initialisation de l'affichage graphique, et dessine le labyrinthe en entier en noir ainsi que la position actuel en bleu(donc le début du labyrinte)
        initgraph(m->l*TAILLE_PIXEL,m->h*TAILLE_PIXEL);
        noir=newcolor(0,0,0);
        bleu=newcolor(0,0,1);
        gris=newcolor(0.1,0.1,0.1);
        cleargraph();
        DessineLab(m,noir);
        DessineCouple(debut,bleu);
        refresh();
    }

    //tant qu'on a pas atteind la fin du labyrinthe
    while(!(compareCouple(parcours->tab[parcours->taille-1],fin)))
    {
        //la position actuelle est celle de la derniere case du parcours
        positionActuelle=parcours->tab[parcours->taille-1];
        //si la position actelle est celle du début, on va d'abord à droite, puis en bas si c'est possible(donc on ajoute la case où l'on va dans le parcours, et dans l'ensemble dejavu
        if(compareCouple(positionActuelle,debut))
        {
            if(!(EnsEstDans(dejavu,construCouple(1,2))))
            {
                tmp=construCouple(1,2);
                EnsAjoute(dejavu,tmp);
                EnsAjoute(parcours,tmp);

                if(affichage==1) DessineCouple(tmp,bleu);
            }
            else
            {
                tmp=construCouple(2,1);
                EnsAjoute(dejavu,tmp);
                EnsAjoute(parcours,tmp);
                if(affichage==1) DessineCouple(tmp,bleu);
            }
        }
        else
        {
            //choix du "pas" c'est à dire de la direction dont on va aller
            pas=choisirchemin_B(parcours,dejavu,m);
            //la positon future sera la position actuelle plus la direction,le "pas", dans laquelle on va aller
            positionFuture=additionCouple(pas,positionActuelle);
            //on ajoute la position actuelle à l'ensemble des cases deja vu (car si on est dessus, on l'a déja vu)
			EnsAjoute(dejavu,positionActuelle);

			//Si la position future correspond à l'avant dernière case du parcours(donc la case "dernière nous"), alors on enlève le dernier élément de parcours(l'algorithme "recule") et on dessine en gris la d'où on vient
            if(compareCouple(positionFuture,parcours->tab[parcours->taille-2])==1)
            {
                EnsSupprDernier(parcours);
                if(affichage==1) DessineCouple(positionActuelle,gris);
            }
            //sinon on avance(ajoute au parcours la position future) vers la position future, qu'on dessine en bleu si l'affichage est activé,
            else
            {
                EnsAjoute(parcours,positionFuture);
                if(affichage==1) DessineCouple(positionFuture,bleu);
            }
        }
        if(affichage==1)
        {
			refresh();
		}
    }

    if(affichage==1)
    {
        waitgraph();
        closegraph();
    }
    //désallocation des ensembles
    EnsFree(parcours);
    EnsFree(dejavu);

    return m;
}

//Choisit le chemin en fonction de la d'ou on vient, et des chemins disponibles, revient en arrière si aucun chemin n'est disponible(cul de sac)
Couple choisirchemin_A(Ens parcours,Ens dejavu,Matrice m)
{
    Couple direction={0,0},provenance={0,0};
    Couple tmp=parcours->tab[parcours->taille-1];
    //provenance contient le vecteur directeur de l'avancé de l'algorithme, ex : s'il vient de gauche provenance = {1,0}
    provenance=construCouple(zeroOuUn(tmp.x - parcours->tab[parcours->taille-2].x),zeroOuUn(tmp.y - parcours->tab[parcours->taille-2].y));
    //ici on teste les préférences : si on ne vient pas de la droite, qu'on est jamais aler à droite, et que la droite n'est pas un mur, alors la direction sera la droite, et sinon on fait la même chose pour le bas,puis le haut, puis à gauche
    if((provenance.x !=-1) && (m->tab[tmp.x+1][tmp.y] != True)&& !(EnsEstDans(dejavu,construCouple(tmp.x+1,tmp.y)))) direction = construCouple(1,0);
    else if((provenance.y!=-1) && (m->tab[tmp.x][tmp.y+1] != True) && !(EnsEstDans(dejavu,construCouple(tmp.x,tmp.y+1)))) direction = construCouple(0,1);
    else if((provenance.y!= 1) && (m->tab[tmp.x][tmp.y-1] != True) && !(EnsEstDans(dejavu,construCouple(tmp.x,tmp.y-1)))) direction = construCouple(0,-1);
    else if((provenance.x!= 1) && (m->tab[tmp.x-1][tmp.y] != True) && !(EnsEstDans(dejavu,construCouple(tmp.x-1,tmp.y)))) direction = construCouple(-1,0);
    else direction = construCouple(0-provenance.x,0-provenance.y);//si ne peux pas avancer librement(c'est à dire, qu'on ne peut aller que la où l'on n'est pas encore aller) ni a droite,ni bas,ni haut,ni gauche, alors on recule(opposé de provenance)
    return direction;
}

Couple choisirchemin_B(Ens parcours,Ens dejavu,Matrice m)
{
    Couple direction={0,0},provenance={0,0};
    int compteur_chemin=0;
    Couple tab[3];//tableau des directions possible, il ne peut en avoir que 3 maximum
    Couple tmp=parcours->tab[parcours->taille-1];
    //Calcule de la provance, ancien vecteur directeur de l'algorithme
    provenance=construCouple(zeroOuUn(tmp.x - parcours->tab[parcours->taille-2].x),zeroOuUn(tmp.y - parcours->tab[parcours->taille-2].y));
    //A partir de la provenance, on regarde les 3 autres chemins possibles : si il y a un chemin(pas de mur) et que l'on y a pas encore arpenté cette direction, on ajoute cette direction au tableau des directions possibles
    if((m->tab[tmp.x+provenance.x][tmp.y+provenance.y] != True) && !(EnsEstDans(dejavu,construCouple(tmp.x+provenance.x,tmp.y+provenance.y))))
    {
		tab[compteur_chemin]=construCouple(provenance.x,provenance.y);
		compteur_chemin++;
    }
    if((m->tab[tmp.x+provenance.y][tmp.y+provenance.x] != True) && !(EnsEstDans(dejavu,construCouple(tmp.x+provenance.y,tmp.y+provenance.x))))
    {
		tab[compteur_chemin]=construCouple(provenance.y,provenance.x);
		compteur_chemin++;
	}

    if((m->tab[tmp.x-provenance.y][tmp.y-provenance.x] != True) && !(EnsEstDans(dejavu,construCouple(tmp.x-provenance.y,tmp.y-provenance.x))))
    {
		tab[compteur_chemin]=construCouple(-provenance.y,-provenance.x);
		compteur_chemin++;
	}
    //Si le compteur de chemin est supérieur à 0, ça veut dire qu'il y a au moins un chemin que l'on peut arpenter librement, on fait un rand() pour choisir la direction que l'on va prendre
    if(compteur_chemin > 0)
    {
		direction=tab[rand() % compteur_chemin];
    }
    //sinon ca veut dire qu'il n'y a pas de chemin disponible, il faut donc reculer(l'opposé de provenance)
    else direction=construCouple(-provenance.x,-provenance.y);
    //on renvoie le nouveau vecteur directeur de l'algorithme
    return direction;
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

void DessineLab(Matrice m,long couleur)
{
    int i,j;
    for(j=0;j<m->h;j++)
    {
        for(i=0;i<m->l;i++)if(m->tab[i][j] == True) DessineCouple(construCouple(i,j),couleur);
    }
}

void EffaceCouple(Couple c)
{
	DessineCouple(c,newcolor(1,1,1));
}

void EffaceEns(Ens e)
{
	DessineEns(e,newcolor(1,1,1));
}
