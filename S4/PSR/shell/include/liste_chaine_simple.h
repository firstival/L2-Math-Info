/** \file
 * Header : Liste chainée simple
 **/

#ifndef __LISTE_CHAINE_SIMPLE_H
#define __LISTE_CHAINE_SIMPLE_H

#include <stdio.h>
#include <stdlib.h>
//Structure contant le pid du processus, ainsi que la chaine de caractère rentré pour lancé la commande
typedef struct { int pid;char * commande;} Commande;

typedef Commande S_LISTE_CHAINE_SIMPLE;

typedef struct StrListeElem { S_LISTE_CHAINE_SIMPLE val; struct StrListeElem * suiv;} StrListeElem, * ListeElem;
typedef struct StrListe {ListeElem t ; ListeElem q;int taille; }StrListe, *Liste;

//Alloue la structure de la liste, et initialise la taille à 0
Liste listenouv();
//Ajoute en tête une élément (et donc alloue le StrListeElem associé)
Liste adjt(Liste l,S_LISTE_CHAINE_SIMPLE a);
//Supprime (et désalloue) l'élément en tête de la liste
Liste supt(Liste l);
//Ajoute en queue une élément (et donc alloue le StrListeElem associé)
Liste adjq(Liste l,S_LISTE_CHAINE_SIMPLE a);
//Supprime (et désalloue) l'élément en queue de la liste
Liste supq(Liste l);
//remplace la valeur de l'élément à l'indice indiqué
Liste remplacerIndice(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice);
//renvoie la valeur de la tete de liste
S_LISTE_CHAINE_SIMPLE tete(Liste l);
//renvoie la valeur de la queue de liste
S_LISTE_CHAINE_SIMPLE dernier(Liste l);
//test de vacuité de la liste
int estvide(Liste l);
//renvoie la taille de la liste
int tailleliste(Liste l);
//Affiche les valeurs contenu dans la liste
void afficherliste(Liste l);
//Insère un élément à l'indice indique (l'élément est alloué)
Liste inserer(Liste l,S_LISTE_CHAINE_SIMPLE a,int indice);
//Suprimme l'élément à l'indice indiqué
Liste supprIndice(Liste l,int indice);
//Renvoie l'adresse associé à un élément de la liste
ListeElem adresseIeme(Liste l,int i);
//Désalloue tout les élément de la liste ainsi que la structure de la liste
void freeListe(Liste l);



#endif

