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
 *fonction qui ajoute un �l�ment "x" en queue de file
 * \param [in] f une File
 * \param [in] x l'�l�ment de type S � ajouter
 * \return un pointeur File dont on a ajout� en queue l'�l�ment x
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
 *fonction qui supprime l'�l�ment en t�te de file
 * \param [in] f une File
 * \return un pointeur File qui est l'adresse du nouveau StrFile en tete(ancien second)
 * \pre
 * \post le StrFile anciennement en t�te a �t� d�sallou�
 */
File FileSupT(File f)
{
	File f_temp=NULL;
	f_temp=f->suivant;
	free(f);
	return f_temp;
}

/** \memberof File
 *fonction qui renvoie la valeur de l'�l�ment de t�te de file
 * \param [in] f un File
 * \return la t�te de la file de type \a S
 * \pre La file en param�tre ne doit pas �tre vide
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
 *fonction qui renvoie le nombre d'�l�ments qu'une file
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
 *fonction qui renvoie le i�me �l�ment d'une file
 * \param [in] f un File
 * \param [in] i un entier
 * \return la valeur du i�me �l�ment de la file
 * \pre i doit �tre sup�rieurs ou �gal � 0, et inf�rieur � taille de la file.
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
 *fonction qui d�truit une file f
 * \param [in] f un File
 * \post D�sallocation de toute les StrFile constituant la file
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
