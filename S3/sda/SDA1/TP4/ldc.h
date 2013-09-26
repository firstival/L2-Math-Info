/** \file ldc.h */

#include "truc.h"

#ifndef _LDC_H_
#define _LDC_H_

/** \class LDC
 * LDC = Liste doublement chaînée de Truc
 */
typedef struct listeDCh 
{
	Truc m;                  /**< ce qu'on stocke dans les LDC */
	struct listeDCh *suiv,   /**< élément suivant dans la LDC */
	                *prec;   /**< élément précédent dans la LDC */
}
LDC, * pLDC;

LDC *LDCAlloc(void);
void LDCFree( LDC *l );

void LDCInsere( LDC **l, Truc t );
void LDCSupprime( LDC **l );
void LDCEchange( LDC **l );

LDC *LDCSuivant( LDC *l );
LDC *LDCPrecedent( LDC *l );
int  LDCEstVide( LDC *l );
int  LDCDebut( LDC *l );
LDC *LDCiieme( LDC *l, int i );
int  LDCLongueur( LDC *l );

void Normalise( LDC **P );

#endif /* #ifndef _LDC_H_ */
