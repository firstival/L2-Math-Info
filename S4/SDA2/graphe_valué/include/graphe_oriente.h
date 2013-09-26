#ifndef GRAPHE_ORIENTE_H
#define GRAPHE_ORIENTE_H

#include <stdio.h>
#include <stdlib.h>

typedef int S_GRAPHE_ORIENTE;
typedef int S_GRAPHE_VALUATION;

typedef struct {int x;int y;S_GRAPHE_VALUATION va;} arc;
typedef struct { S_GRAPHE_ORIENTE x;S_GRAPHE_VALUATION v;} couple;

typedef struct strarc {
	S_GRAPHE_ORIENTE v;
	S_GRAPHE_VALUATION va;
	struct strarc * succ;
	}Strarc, * Listearc;
	
typedef struct strsom {
	S_GRAPHE_ORIENTE v;
	struct strsom * suiv;
	Listearc ls;
	}Strsom, *Graphe;

/*
 * Opération en _1 : opération sur les liste d'arc
 * Opération en _2 : opération sur les liste de sommet (Graphe)
 * A faire : tester les fonctions, 1 seul parcours pour sups
 **/

Listearc newArc(S_GRAPHE_ORIENTE v,S_GRAPHE_VALUATION va);
Listearc insertion_1(Listearc l,S_GRAPHE_ORIENTE v,S_GRAPHE_VALUATION va);
Listearc sup_1(Listearc l,S_GRAPHE_ORIENTE v);
Listearc rech_1(Listearc l,S_GRAPHE_ORIENTE v);
Listearc supall_1(Listearc l);

Graphe newSommet(S_GRAPHE_ORIENTE v);
Graphe insertion_2(Graphe g,S_GRAPHE_ORIENTE v);
Graphe sup_2(Graphe g,S_GRAPHE_ORIENTE v);
Graphe rech_2(Graphe g,S_GRAPHE_ORIENTE v);	



Graphe grnouv();
Graphe adjs(Graphe g,S_GRAPHE_ORIENTE x);//Ajout d'un sommet au graphe
Graphe adja(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y,S_GRAPHE_VALUATION va);//Ajout d'un arc sur un sommet du graphe
int exs(Graphe g,S_GRAPHE_ORIENTE x);//Vérifie l'éxistence d'un sommet
int exa(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y);//Vérifie l'existence d'un arc
Graphe sups(Graphe g,S_GRAPHE_ORIENTE x);//Supprime un sommet du graphe (ainsi que les arcs associés)
Graphe supa(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y);//Supprime un arc associé à un sommet du graphe
int nb_sommet(Graphe g);
void afficheGraphe(Graphe g);

Listearc lsuc(Graphe g,S_GRAPHE_ORIENTE x);
Listearc lpred(Graphe g,S_GRAPHE_ORIENTE x);
int de(Graphe g,S_GRAPHE_ORIENTE x);
int di(Graphe g,S_GRAPHE_ORIENTE x);
Graphe supsuc(Graphe g,S_GRAPHE_ORIENTE x);
Graphe suppred(Graphe g,S_GRAPHE_ORIENTE x);


//Effectuer l'algo de prim pour déterminer un arbre couvrant
Graphe prim(Graphe g);
//recherche l'arc (x,y,v) tel que il x appartient à a, y à g privé de a, et que v est la valeur minimal possible de tout les arcs possibles
arc rech_sommet_sortant_minimisant(S_GRAPHE_ORIENTE * sommet_restant,Graphe g,Graphe a);
//Recherche le couple (x,d) tel que x appartient a l'arbre couvrant a, que z appartient a g privé de a, et d est la valuation minimum entre z et un sommet de a
couple rech_couple_mini(S_GRAPHE_ORIENTE z,Graphe g,Graphe a);


#endif
