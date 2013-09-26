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
 * header pour les matrices
 * \author Vincent Loechner, copyright GPLv3+
 */

/**
 * le type truc : flotant double précision
 */
typedef double Truc;

/**
 * taille max d'une matrice
 */
#define MAX 20

/**
 * structure de matrice
 */
struct matrice
{
	int hauteur;      /**< hauteur de la matrice */
	int largeur;      /**< largeur de la matrice */
	Truc m[MAX][MAX]; /**< éléments de la matrice */
};

/**
 * évite de taper struct à chaque fois
 */
typedef struct matrice Matrice;


extern Matrice NouvelleMatrice( int h, int l );
extern Matrice AdditionneMatrices( Matrice a, Matrice b );
extern Truc ElemMatrice( Matrice m, int l, int c );
extern int EstNulMatrice( Matrice m );
