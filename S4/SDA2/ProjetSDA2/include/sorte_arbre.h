#ifndef __SORTE_ARBRE_H
#define __SORTE_ARBRE_H

//typedef union { char c;int v;} op;

typedef int ARBRE_BIN_S;

typedef struct strarbin {
		struct strarbin * g, *d;
		ARBRE_BIN_S v;
	} StrArbin, * Arbin;

#endif
