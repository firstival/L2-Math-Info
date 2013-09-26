/** \file */

#include "files_fct.h"

/** \memberof StrFile
 * fonction qui renvoie une nouvelle File vide
 * \return liste vide de taille 0 et position 0
 * \pre
 * \post
 */
File FileNouv()
{
	File f;
	f.position=0;
	f.taille=0;
	return f;
}


/** \memberof StrFile
 *fonction qui ajoute un élément "x" en queue de File
 * \param [in] f une File
 * \param [in] x l'élément de type S à ajouter
 * \return une File dont on a ajouté en queue l'élément x
 * \pre (f.taille + 1) inférieur à \a N
 * \post
 */
File FileAdjQ(File f,S x)
{
	f.t[(f.taille+f.position) % N]=x;
	f.taille++;
	return f;
}

/** \memberof StrFile
 *fonction qui supprime l'élément en tête de File
 * \param [in] f une File
 * \return une File dont on a enlevé la tête
 * \pre La list en paramètre ne doit pas être vide
 * \post
 */
File FileSupT(File f)
{
	f.position=(f.position+1)%N;
	f.taille--;
	return f;
}

/** \memberof StrFile
 *fonction qui renvoie la valeur de l'élément de tête de File
 * \param [in] f une File
 * \return la tête de la File de type \a S
 * \pre La liste en paramètre ne doit pas être vide
 * \post
 */
S FileTete(File f)
{
	return f.t[f.position];
}

/** \memberof StrFile
 *fonction qui teste si une File est vide
 * \param [in] f une File
 * \return 1 si la File est vide, 0 si elle est remplie
 * \pre
 * \post
 */
int FileEstVide(File f)
{
	return (f.taille == 0);
}

/** \memberof StrFile
 *fonction qui renvoie le nombre d'éléments qu'une File
 * \param [in] f une File
 * \return la taille de la File
 * \pre
 * \post
 */
int FileTaille(File f)
{
	return f.taille;
}

/** \memberof StrFile
 *fonction qui renvoie le ième élément d'une File
 * \param [in] f une File
 * \param [in] i un entier
 * \return la valeur du ième élément de la File
 * \pre 0<= i < f.taille : i doit être supérieurs ou égal à 0, et inférieur à taille.
 * \post
 */
S FileIeme(File f,int i)
{
	return f.t[(f.position + i-1)%N];
}

/** \memberof StrFile
 *fonction qui détruit une File f (ne fait rien en programmation fonctionnelle, mais elle sera utile en programmation par mutation
 * \param [in] f une File
 * \pre
 * \post
 */
void FileDetruit(File f)
{

}
