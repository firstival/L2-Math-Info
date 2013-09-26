#ifndef __sorte_arbre_h
#define __sorte_arbre_h


typedef int S;

typedef struct strarbin {
		struct strarbin * g, *d;
		S v;
	} StrArbin, * Arbin;

#endif
