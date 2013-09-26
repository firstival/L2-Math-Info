/** \file
 * Header : Liste chain�e simple
 **/

#ifndef __LISTE_CHAINE_SIMPLE_H
#define __LISTE_CHAINE_SIMPLE_H

#include <stdio.h>
#include <stdlib.h>
//Structure contant le pid du processus, ainsi que la chaine de caract�re rentr� pour lanc� la commande
typedef struct { int pid;char * commande;} Commande;

typedef Commande S_LISTE_CHAINE_SIMPLE;

typedef struct StrListeElem { S_LISTE_CHAINE_SIMPLE val; struct StrListeElem * suiv;} StrListeElem, * ListeElem;
typedef struct StrListe {ListeElem t ; ListeElem q;int taille; }StrListe, *Liste;

//Alloue la structure de la liste, et initialise la taille � 0
Liste listenouv();
//Ajoute en t�te une �l�ment (et donc alloue le StrListeElem associ�)
Liste adjt(Liste l,S_LISTE_CHAINE_SIMPLE a);
//Supprime (et d�salloue) l'�l�ment en t�te de la liste
Liste supt(Liste l);
//Ajoute en queue une �l�ment (et donc alloue le StrListeElem associ�)
Liste adjq(Liste l,S_LISTE_CHAINE_SIMPLE a);
//Supprime (et d�salloue) l'�l�ment en queue de la liste
Liste supq(Liste l);
//remplace la valeur de l'�l�ment � l'indice indiqu�
Liste remplacerIndice(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice);
//renvoie la valeur de la tete de liste
S_LISTE_CHAINE_SIMPLE tete(Liste l);
//renvoie la valeur de la queue de liste
S_LISTE_CHAINE_SIMPLE dernier(Liste l);
//test de vacuit� de la liste
int estvide(Liste l);
//renvoie la taille de la liste
int tailleliste(Liste l);
//Affiche les valeurs contenu dans la liste
void afficherliste(Liste l);
//Ins�re un �l�ment � l'indice indique (l'�l�ment est allou�)
Liste inserer(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice);
//Suprimme l'�l�ment � l'indice indiqu�
Liste supprIndice(Liste l,int indice);
//Renvoie l'adresse associ� � un �l�ment de la liste
ListeElem adresseIeme(Liste l,int i);
//D�salloue tout les �l�ment de la liste ainsi que la structure de la liste
void freeListe(Liste l);



#endif

