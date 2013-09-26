/** \file */
#include "files_ch.h"
#include "sorte.h"


/** \memberof File
 * fonction qui renvoie une nouvelle file vide
 * \return liste vide qui pointe sur NULL
 * \post
 */
File FileNouv()
{
	File f=NULL;
	return f;
}

/** \memberof File
 *fonction qui ajoute un élément "x" en queue de file
 * \param [in] f une File
 * \param [in] x l'élément de type S à ajouter
 * \return un pointeur File dont on a ajouté en queue l'élément x
 * \pre
 * \post allocation d'un StrFile, l'ancier dernier StrFile de la file pointe maintenant sur le nouveau dernier
 */
File FileAdjQ(File f,S x)
{
	File f_adj=malloc(sizeof(StrFile));
	File f_temp=f;
	
	f_adj->suivant=NULL;
	f_adj->v=x;
	if(f==NULL) return f_adj;
	else
	{
		while(f_temp->suivant != NULL)
		{
			f_temp=f_temp->suivant;
		}
	f_temp->suivant=f_adj;
	return f;
	}
 
}

/** \memberof File
 *fonction qui supprime l'élément en tête de file
 * \param [in] f une File
 * \return un pointeur File qui est l'adresse du nouveau StrFile en tete(ancien second)
 * \pre
 * \post le StrFile anciennement en tête a été désalloué
 */
File FileSupT(File f)
{
	File f_temp=NULL;
	f_temp=f->suivant;
	free(f);
	return f_temp;
}

/** \memberof File
 *fonction qui renvoie la valeur de l'élément de tête de file
 * \param [in] f un File
 * \return la tête de la file de type \a S
 * \pre La file en paramètre ne doit pas être vide
 */
S FileTete(File f)
{
	return f->v;
}

/** \memberof File
 *fonction qui teste si une file est vide
 * \param [in] f un File
 * \return 1 si la file est vide, 0 si elle est remplie
 */
int FileEstVide(File f)
{
	return (f==NULL);
}

/** \memberof File
 *fonction qui renvoie le nombre d'éléments qu'une file
 * \param [in] f un File
 * \return la taille de la file
 */
int FileTaille(File f)
{
	int i=0;
	while(f != NULL)
	{
		i++;
		f=f->suivant;
	}
	return i;
}

/** \memberof File
 *fonction qui renvoie le ième élément d'une file
 * \param [in] f un File
 * \param [in] i un entier
 * \return la valeur du ième élément de la file
 * \pre i doit être supérieurs ou égal à 0, et inférieur à taille de la file.
 */
S FileIeme(File f, int i)
{
	int j=0;
	for(j=0;j<i;j++)
	{
		f=f->suivant;
	}
	return f->v;
}

/** \memberof File
 *fonction qui détruit une file f
 * \param [in] f un File
 * \post Désallocation de toute les StrFile constituant la file
 */
void FileDetruit(File f)
{
	File temp=NULL;
	while(f != NULL)
	{
		temp=f;
		f=f->suivant;
		free(temp);
	}
}
