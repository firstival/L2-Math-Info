/** \file */
#include "files_chop.h"
#include "sorte.h"

/** \memberof File
 * fonction qui renvoie une nouvelle file vide
 * \return file vide de taille 0 et tete/queue à NULL
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
 *fonction qui ajoute un élément "x" en queue de file
 * \param [in] f une File
 * \param [in] x l'élément de type S à ajouter
 * \return une File dont on a ajouté en queue l'élément x
 * \pre
 * \post allocation d'un StrFile qui devient le nouvel élément en queue, si f était vide : f.tete pointera sur le nouvel élément, f.queue pointe sur le nouvel élément
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
 *fonction qui supprime l'élément en tête de file
 * \param [in] f une File
 * \return une File dont on a enlevé la tête, dont la taille est diminué de 1, dont f.tete pointe sur la nouvelle tête
 * \pre La file en paramètre ne doit pas être vide
 * \post désallocation de l'ancienne tête
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
 *fonction qui renvoie la valeur de l'élément de tête de file
 * \param [in] f un File
 * \return la tête de la file de type \a S
 * \pre La liste en paramètre ne doit pas être vide
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
 *fonction qui renvoie le nombre d'éléments qu'une file
 * \param [in] f un File
 * \return la taille de la file
 */
int FileTaille(File f)
{
	return f.taille;
}

/** \memberof File
 *fonction qui renvoie le ième élément d'une file
 * \param [in] f une File
 * \param [in] i un entier
 * \return la valeur du ième élément de la file
 * \pre i doit être supérieurs ou égal à 0, et inférieur à f.taille.
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
 *fonction qui détruit une file f
 * \param [in] f une File
 * \post désallocation succéssive de tout les StrFile de la file
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