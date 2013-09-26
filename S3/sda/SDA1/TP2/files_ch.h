/** \file */
#ifndef __FILES_CH_H
#define __FILES_CH_H

#include <stdio.h>
#include <stdlib.h>

#include "sorte.h"
/** Le type File et StrFile
 * \struct StrFile
 *  
 */
typedef struct StrFile
{
	S v;/**<valeur de l'élément de type S */
	struct StrFile * suivant;/**<pointeur sur le prochain StrFile de la file*/
}
StrFile, *File;

File FileNouv();
File FileAdjQ(File f,S x);
File FileSupT(File f);
S FileTete(File f);
int FileEstVide(File f);
int FileTaille(File f);
S FileIeme(File f, int i);
void FileDetruit(File f);

#endif