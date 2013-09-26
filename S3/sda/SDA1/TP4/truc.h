/** \file truc.h */

#ifndef _TRUC_H_
#define _TRUC_H_

/**
 * Un Truc permet de stocker un monome simple variable
 * c'est à dire une expression de la forme (coef * X^degre)
 */
typedef struct
{
	int degre;     /**< degre du monome */
	double coef;   /**< coefficient du monome */
}
Truc;

#endif /* #ifndef _TRUC_H_ */

