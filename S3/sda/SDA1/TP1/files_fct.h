/** \file */

#ifndef __FILES_FCT_H
#define __FILES_FCT_H

#include <stdio.h>
#include "sorte.h"
/**
 * Taille maximum de la file
 */
#define N 50000

/** Le type File
 * \struct StrFile
 *  
 */
typedef struct StrFile
{
    S t[N]; /**< tableau de valeur de type S de la File */
    int position;/**< position de la tête de la File */
    int taille;/**< taille effective de la File */

} File;


File FileNouv();


File FileAdjQ(File f,S x);


File FileSupT(File f);


S FileTete(File f);


int FileEstVide(File f);


int FileTaille(File f);


S FileIeme(File f, int i);


void FileDetruit(File f);




#endif
