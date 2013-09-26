/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** \file
 * matrices : source
 * 
 * \author Vincent Loechner, copyright GPLv3+
 */

#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"


/** \memberof matrice
 * Constructeur: Crée une nouvelle matrice de taille \a h * \a l, initialisée à 0
 * \param [in] h hauteur de la matrice
 * \param [in] l largeur de la matrice
 * \return matrice nulle de taille \a h * \a l
 * \pre 0 <= \a h <= MAX, 0 <= \a l <= MAX
 * \post
 */
Matrice NouvelleMatrice( int h, int l )
{
	Matrice m;
	int i, j;

	if( l<0 || l>MAX || h<0 || h>MAX )
	{
		fprintf( stderr, "NouvelleMatrice: invalid dimensions" );
		exit( -1 );
	}

	m.hauteur = h;
	m.largeur = l;
	for( i=0 ; i<h ; i++ )
		for( j=0 ; j<l ; j++ )
			m.m[i][j] = 0.;

	return( m );
}


/** \memberof matrice
 * Constructeur: additionne deux matrices
 * \param [in] a première matrice
 * \param [in] b deuxième matrice
 * \return la matrice \a a + \a b
 * \pre a.largeur=b.largeur ; a.hauteur=b.hauteur
 * \post
 */
Matrice AdditionneMatrices( Matrice a, Matrice b )
{
	Matrice m;
	int i, j;
	if( a.largeur!=b.largeur || a.hauteur!=b.hauteur )
	{
		fprintf( stderr, "AdditionneMatrices: incompatible dimensions" );
		exit( -1 );
	}
	m.hauteur = a.hauteur;
	m.largeur = a.largeur;
	for( i=0 ; i<m.hauteur ; i++ )
		for( j=0 ; j<m.largeur ; j++ )
			m.m[i][j] = a.m[i][j] + b.m[i][j];

	return( m );
}


/** \memberof matrice
 * Sélecteur : renvoie l'élément de matrice aux coordonnées passées en paramètre
 * \param [in] m matrice
 * \param [in] l numéro de ligne de la matrice
 * \param [in] c numéro de colonne de la matrice
 * \return valeur de \a m[\a l][\a c]
 * \pre 0 <= l < m.hauteur ; 0 <= c < m.largeur
 * \post
 */
Truc ElemMatrice( Matrice m, int l, int c )
{
	if( c<0 || c>=m.largeur || l<0 || l>m.hauteur )
	{
		fprintf( stderr, "ElemMatrices: out of matrix" );
		exit( -1 );
	}

	return( m.m[l][c] );
}

/** \memberof matrice
 * Sélecteur : Teste si une matrice est nulle (si tous ses éléments sont nuls)
 * \param [in] m matrice à tester
 * \return vrai si tous les éléments de \a m sont nuls, faux sinon
 * \pre
 * \post
 */
int EstNulMatrice( Matrice m )
{
	int i, j;
	for( i=0 ; i<m.hauteur ; i++ )
		for( j=0 ; j<m.largeur ; j++ )
			if( m.m[i][j] != 0. )
				return( 0 );

	return( 1 );
}

