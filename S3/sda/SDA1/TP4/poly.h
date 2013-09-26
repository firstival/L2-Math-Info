/** \file poly.h
 * structures de données et déclarations pour les polynômes
 */

#include "truc.h"
#include "ldc.h"
#include <stdio.h>

#ifndef _POLY_H_
#define _POLY_H_

/**
 * Un monôme simple variable est un Truc,
 * défini dans truc.h
 */
typedef Truc Monome;

/** \class Polynome
 * Un polynôme est une liste doublement chaînée de monômes,
 * définie dans ldc.h
 * Attention, la liste doublement chaînée est toujours stockée dans
 * l'ordre des degrés des monômes qui la constituent.
 * Il n'y a pas de doublon de monômes de même degré.
 */
typedef LDC *Polynome;

Polynome PolyCopie( Polynome P );

Polynome PolyAdd( Polynome P1, Polynome P2 );
Polynome PolyMul( Polynome P1, Polynome P2 );
Polynome PolyDerive( Polynome P1 );

Polynome PolyRead( FILE *f );
void     PolyWrite( FILE *f, Polynome P );

#endif /* #ifndef _POLY_H_ */

