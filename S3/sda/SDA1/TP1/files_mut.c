/** \file */

#include "files_mut.h"

/** \memberof File
 * fonction qui renvoie une nouvelle file vide
 * \return liste vide de taille 0 et position 0
 * \post allocation d'un type StrFile
 */
File FileNouv()
{
	File f=NULL;
	f=(File)malloc(sizeof(StrFile));
	f->position=0;
	f->taille=0;
	return f;
}


/** \memberof File
 *fonction qui ajoute un élément "x" en queue de file
 * \param [in] f un File
 * \param [in] x l'élément de type S à ajouter
 * \return un pointeur File dont on a ajouté en queue de la StrFile pointée l'élément x
 * \pre (f.taille + 1) inférieur à \a N
 * \post le StrFile pointée voit sa taille augmentée de 1, et un élément est ajouté à son tableau en queue
 */
File FileAdjQ(File f,S x)
{
	f->t[(f->taille+f->position) % N]=x;
	f->taille++;
	return f;
}

/** \memberof File
 *fonction qui supprime l'élément en tête de file
 * \param [in] f un File
 * \return un pointeur File dont on a enlevé la tête de la StrFile pointée
 * \pre La list en paramètre ne doit pas être vide
 * \post le StrFile pointée voit sa taille diminué de 1
 */
File FileSupT(File f)
{
	f->position=(f->position+1)%N;
	f->taille--;
	return f;
}

/** \memberof File
 *fonction qui renvoie la valeur de l'élément de tête de file
 * \param [in] f un File
 * \return la tête de la file de type \a S
 * \pre La liste en paramètre ne doit pas être vide
 */
S FileTete(File f)
{
	return f->t[f->position];
}

/** \memberof File
 *fonction qui teste si une file est vide
 * \param [in] f un File
 * \return 1 si la file est vide, 0 si elle est remplie
 */
int FileEstVide(File f)
{
	return (f->taille == 0);
}

/** \memberof File
 *fonction qui renvoie le nombre d'éléments qu'une file
 * \param [in] f un File
 * \return la taille de la file
 */
int FileTaille(File f)
{
	return f->taille;
}

/** \memberof File
 *fonction qui renvoie le ième élément d'une file
 * \param [in] f un File
 * \param [in] i un entier
 * \return la valeur du ième élément de la file
 * \pre 0<= i < f.taille : i doit être supérieurs ou égal à 0, et inférieur à taille.
 */
S FileIeme(File f,int i)
{
	return f->t[(f->position + i-1)%N];
}

/** \memberof File
 *fonction qui détruit une file f (ne fait rien en programmation fonctionnelle, mais elle sera utile en programmation par mutation
 * \param [in] f un File
 * \post suppression du File en paramètre par un free
 */
void FileDetruit(File f)
{

}
