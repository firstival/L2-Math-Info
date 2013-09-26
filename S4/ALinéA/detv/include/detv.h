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
 * Fonction qui gère le SIGALRM pour le processus fils qui calcule les déterminants de manière récursive
 * \param [in] : int signum, le numéro du signal
 * \post le FILE dans lequel le processus fils écrivait est fermé (fclose), un message d'erreur est affiché sur stderr
 **/
void handler_sigalrm_ech(int signum);
/**
 * Fonction qui gère le SIGALRM pour le processus fils qui calcule les déterminants en triangularisant la matrice
 * \param [in] : int signum, le numéro du signal
 * \post le FILE dans lequel le processus fils écrivait est fermé (fclose), un message d'erreur est affiché sur stderr
 **/
void handler_sigalrm_rec(int signum);
/**
 * Fonction qui gère le signal SIGINT pour le processus père principale : Il envoie SIGALRM a ses deux fils, puis attend leur terminaisons
 * \param [in] : int signum, le numéro du signal
 * \post On envoie le signal SIGALRM au deux processus fils, puis on attend leur terminaisons
 **/
void handler_sigint(int signum);

#endif