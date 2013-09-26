/** \file
 * Header : detv
 **/

#ifndef __DETV_H
#define __DETV_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define TEMPS_MAX 3600

#include "ALineA-TP2.h"

/**
 * Fonction qui g�re le SIGALRM pour le processus fils qui calcule les d�terminants de mani�re r�cursive
 * \param [in] : int signum, le num�ro du signal
 * \post le FILE dans lequel le processus fils �crivait est ferm� (fclose), un message d'erreur est affich� sur stderr
 **/
void handler_sigalrm_ech(int signum);
/**
 * Fonction qui g�re le SIGALRM pour le processus fils qui calcule les d�terminants en triangularisant la matrice
 * \param [in] : int signum, le num�ro du signal
 * \post le FILE dans lequel le processus fils �crivait est ferm� (fclose), un message d'erreur est affich� sur stderr
 **/
void handler_sigalrm_rec(int signum);
/**
 * Fonction qui g�re le signal SIGINT pour le processus p�re principale : Il envoie SIGALRM a ses deux fils, puis attend leur terminaisons
 * \param [in] : int signum, le num�ro du signal
 * \post On envoie le signal SIGALRM au deux processus fils, puis on attend leur terminaisons
 **/
void handler_sigint(int signum);

#endif