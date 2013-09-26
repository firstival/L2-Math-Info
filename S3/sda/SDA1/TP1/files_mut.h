/** \file */

#ifndef __File_H
#define __File_H

#include <stdio.h>
#include <stdlib.h>
#include "sorte.h"

#define N 50000


/** Le type File : pointeur sur un un type StrFile */
typedef struct StrFile
{
    S t[N]; /**< tableau de valeur de type S de la file */
    int position;/**< position de la tête de la file */
    int taille;/**< taille effective de la file */

}StrFile, *File;


File FileNouv();

File FileAdjQ(File f,S x);

File FileSupT(File f);

S FileTete(File f);

int FileEstVide(File f);

int FileTaille(File f);

S FileIeme(File f, int i);

void FileDetruit(File f);



#endif
