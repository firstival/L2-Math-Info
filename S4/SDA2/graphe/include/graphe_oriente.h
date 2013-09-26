#ifndef GRAPHE_ORIENTE_H
#define GRAPHE_ORIENTE_H

#include <stdio.h>
#include <stdlib.h>

typedef int S_GRAPHE_ORIENTE;

typedef struct strarc {
	S_GRAPHE_ORIENTE v;
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

Listearc newArc(S_GRAPHE_ORIENTE v);
Listearc insertion_1(Listearc l,S_GRAPHE_ORIENTE v);
Listearc sup_1(Listearc l,S_GRAPHE_ORIENTE v);
Listearc rech_1(Listearc l,S_GRAPHE_ORIENTE v);
Listearc supall_1(Listearc l);

Graphe newSommet(S_GRAPHE_ORIENTE v);
Graphe insertion_2(Graphe g,S_GRAPHE_ORIENTE v);
Graphe sup_2(Graphe g,S_GRAPHE_ORIENTE v);
Graphe rech_2(Graphe g,S_GRAPHE_ORIENTE v);	



Graphe grnouv();
Graphe adjs(Graphe g,S_GRAPHE_ORIENTE x);//Ajout d'un sommet au graphe
Graphe adja(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y);//Ajout d'un arc sur un sommet du graphe
int exs(Graphe g,S_GRAPHE_ORIENTE x);//Vérifie l'éxistence d'un sommet
int exa(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y);//Vérifie l'existence d'un arc
Graphe sups(Graphe g,S_GRAPHE_ORIENTE x);//Supprime un sommet du graphe (ainsi que les arcs associés)
Graphe supa(Graphe g,S_GRAPHE_ORIENTE x,S_GRAPHE_ORIENTE y);//Supprime un arc associé à un sommet du graphe
void afficheGraphe(Graphe g);

Listearc lsuc(Graphe g,S_GRAPHE_ORIENTE x);
Listearc lpred(Graphe g,S_GRAPHE_ORIENTE x);
int de(Graphe g,S_GRAPHE_ORIENTE x);
int di(Graphe g,S_GRAPHE_ORIENTE x);
Graphe supsuc(Graphe g,S_GRAPHE_ORIENTE x);
Graphe suppred(Graphe g,S_GRAPHE_ORIENTE x);



#endif
