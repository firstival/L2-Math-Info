/** \file */
#ifndef __FILES_CHOPT_H
#define __FILES_CHOPT_H

#include <stdio.h>
#include <stdlib.h>

#include "sorte.h"
/** Le type StrFile, �l�ment d'une file
 * \struct StrFile
 *
*/
typedef struct StrFile{
	S v;/**<valeur de l'�l�ment de type \a S*/
	struct StrFile * suivant;/**<pointeur sur le prochain �l�ment de la file*/
}
StrFile;

/**Le type File, repr�sentant une file
 * \struct File
 */
typedef struct {
int taille;/**<taille de la file*/
StrFile * tete;/**<pointeur sur la t�te de la file*/
StrFile * queue;/**<pointeur sur la queue de la file*/
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
