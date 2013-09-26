/** \file */
#include "files_chop.h"
#include "sorte.h"

/** \memberof File
 * fonction qui renvoie une nouvelle file vide
 * \return file vide de taille 0 et tete/queue � NULL
 * \post
 */
File FileNouv()
{
	File f;
	f.taille=0;
	f.tete=NULL;
	f.queue=NULL;
	return f;
}

/** \memberof File
 *fonction qui ajoute un �l�ment "x" en queue de file
 * \param [in] f une File
 * \param [in] x l'�l�ment de type S � ajouter
 * \return une File dont on a ajout� en queue l'�l�ment x
 * \pre
 * \post allocation d'un StrFile qui devient le nouvel �l�ment en queue, si f �tait vide : f.tete pointera sur le nouvel �l�ment, f.queue pointe sur le nouvel �l�ment
 */
File FileAdjQ(File f,S x)
{
	StrFile * add=(StrFile *)malloc(sizeof(StrFile));
	add->v=x;
	add->suivant=NULL;
	if(f.tete == NULL)f.tete=add;
	else f.queue->suivant = add;
	f.queue=add;
	f.taille++;
	return f;
}

/** \memberof File
 *fonction qui supprime l'�l�ment en t�te de file
 * \param [in] f une File
 * \return une File dont on a enlev� la t�te, dont la taille est diminu� de 1, dont f.tete pointe sur la nouvelle t�te
 * \pre La file en param�tre ne doit pas �tre vide
 * \post d�sallocation de l'ancienne t�te
 */
File FileSupT(File f)
{
	StrFile * temp=f.tete;
	f.tete=f.tete->suivant;
	f.taille--;
	free(temp);
	return f;
}

/** \memberof File
 *fonction qui renvoie la valeur de l'�l�ment de t�te de file
 * \param [in] f un File
 * \return la t�te de la file de type \a S
 * \pre La liste en param�tre ne doit pas �tre vide
 */
S FileTete(File f)
{
	return f.tete->v;
}

/** \memberof File
 *fonction qui teste si une file est vide
 * \param [in] f un File
 * \return 1 si la file est vide, 0 si elle est remplie
 */
int FileEstVide(File f)
{
	return f.taille==0;
}

/** \memberof File
 *fonction qui renvoie le nombre d'�l�ments qu'une file
 * \param [in] f un File
 * \return la taille de la file
 */
int FileTaille(File f)
{
	return f.taille;
}

/** \memberof File
 *fonction qui renvoie le i�me �l�ment d'une file
 * \param [in] f une File
 * \param [in] i un entier
 * \return la valeur du i�me �l�ment de la file
 * \pre i doit �tre sup�rieurs ou �gal � 0, et inf�rieur � f.taille.
 */
S FileIeme(File f, int i)
{
	StrFile * temp=f.tete;
	int c=0;
	for(c=1;c<i;c++)
	{
		temp=temp->suivant;
	}
	return temp->v;
}	

/** \memberof File
 *fonction qui d�truit une file f
 * \param [in] f une File
 * \post d�sallocation succ�ssive de tout les StrFile de la file
 */
void FileDetruit(File f)
{
	StrFile * temp=f.tete;
	while(f.tete != NULL)
	{
		f.tete=f.tete->suivant;
		free(temp);
		temp=f.tete;
	}	
}