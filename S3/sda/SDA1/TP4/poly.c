/** \file poly.c
 * fonctions de manipulation de polynômes
 */

#include "poly.h"

/** \memberof Polynome
 * Constructeur : additionne deux polynômes
 * \param [in] P1 premier polynôme
 * \param [in] P2 deuxième polynôme
 * \return le polynôme (P1+P2)
 * \pre 
 * \post
 */
Polynome PolyAdd( Polynome P1, Polynome P2 )
{
	pLDC fin=NULL,debut=NULL;
}

/** \memberof Polynome
 * Constructeur : multiplie deux polynômes
 * \param [in] P1 premier polynôme
 * \param [in] P2 deuxième polynôme
 * \return le polynôme (P1*P2)
 * \pre 
 * \post
 */
Polynome PolyMul( Polynome P1, Polynome P2 )
{
	
}

/** \memberof Polynome
 * Constructeur : calcule la dérivée d'un polynôme
 * \param [in] P1 polynôme à dériver
 * \return le polynôme P1'
 * \pre 
 * \post
 */
Polynome PolyDerive( Polynome P1 )
{
	
}

/** \memberof Polynome
 * Constructeur : Lit un polynôme depuis un fichier f
 * \param [in] f fichier à utiliser en entrée
 * \return le polynôme lu
 * \pre 
 * \post
 */
Polynome PolyRead( FILE *f )
{
	
}

/** \memberof Polynome
 * Sélecteur : affiche un polynôme dans le fichier f
 * \param [in] f fichier à utiliser en sortie
 * \param [in] P polynôme à afficher
 * \return 
 * \pre 
 * \post
 */
void     PolyWrite( FILE *f, Polynome P )
{
	
}
