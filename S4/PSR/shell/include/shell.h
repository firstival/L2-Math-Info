/** \file
 * Header : Shell
 **/

#ifndef __SHELL_H
#define __SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#include "liste_chaine_simple.h"


#define TAILLE_INPUT 255


int estExit(char * t);
/**
 * Fonction qui calcule la taille de la chaine de caractères
 * \param [in] : char *, pointeur sur une chaine de caractères
 * \return int, la taille de la chaine de caractères
 * \pre la chaine de caractère doit se finir par un '\0'
 * \post
 **/
int taille_tableau(char * tab);

/**
 * Fonction qui free le tableau ainsi que les chaines contenu dedans
 * \param [in] : char **, tableau de chaine de caractères
 * \pre le tableau doit finir par un pointeur NULL
 * \post la mémoire a été libéré, il ne faudra plus accéder au tableau plus tard
 **/
void freeArg(char ** tab);

/**
 * Fonction qui attend la terminaison (avec WNOHANG) de tout les processus fils contenu dans la liste en entrée
 * \param [in] : Liste l, La liste de processus lancé avec "&" dont on a pas encore enregistré la mort
 * \pre La liste doit être correctement alloué par listenouv()
 * \post Les processus fils dont la fonction a enregistré la mort on été supprimé de la liste
 **/
void wait_hidden_child(Liste l);

/**
 * Fonction qui élimine tout les espaces inutiles à la fin d'une chaine de caractères
 * \param [in] : char * input, une chaine de caractères dont on doit éliminer les espaces (éventuelle) de fin
 * \param [in] : int n, la taille de la chaine de caractères
 * \return la chaine de caractères modifié
 * \post La chaine de caractères a été modifié
 **/
char * elimine_espace_fin(char * input,int n);

/**
 * Fonction qui calcule le nombre d'occurence d'un caractère dans une chaine de caractère
 * \param [in] : char * tab, une chaine de caractère
 * \param [in] : char c, le caractère dont on controle l'occurence
 * \return le nombre d'occurence du caractère
 * \pre la chaine de caractère doit se finir par '\0'
 **/
int compte_char(char * tab,char c);

/**
 * Fonction qui cherche l'indice dans le tableau de la chaine de caractère un certain caractère
 * \param [in] : char * tab, une chaine de caractère
 * \param [in] : char c, le caractère à rechercher
 * \return -1 si le caractère n'est pas trouvé, la position de la 1er occurence du caractère recherché sinon
 * \pre tab doit se finir par un '\0'
 **/
int recherche(char * tab,char c);

/**
 * Fonction qui sépare les mots d'une chaine de caractère et les place dans un tableau de chaine de caractère
 * \param [in] : char * tab, une chaine de caractère
 * \return un tableau de chaine de caractères contenant les mots de la chaine passé en argument
 * \pre tab doit être fini par '\0'
 * \post tab est modifié (il ne contient plus la chaine de caractères), et un tableau de chaine de caractère a été alloué
 **/
char * * separation_argument(char * tab);

/**
 * Fonction appelle shell_aux et met en place la redirection des signaux
 **/
int shell();

/**
 * Fonction qui demande une saisi au clavier, créer une processus enfant, et lui faire exec la commande tapé au clavier. Elle gère l'enregistrement de la mort des fils.
 */
void shell_aux();



#endif
