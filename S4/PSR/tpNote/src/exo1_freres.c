#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

#include "exo1_freres.h"

#define MAX_PROC 100


pid_t * tabPID=NULL;
pid_t PID_PERE;

int TAILLE=0;
int continuerAttendreFrere=1;
int pausePere=1;


/* toutes ces fonctions retournent 0 en cas de succès, un code d'erreur différent de 0 sinon */

/* fonction appelée avant toute création des nouveaux processus */
int init_freres()
{
	struct sigaction handler1;
	struct sigaction handler2;
	
	sigemptyset(&handler1.sa_mask);
	sigemptyset(&handler2.sa_mask);
	
	handler1.sa_flags=SA_SIGINFO;
	
	handler1.sa_sigaction=handler_SIGUSR1;
	handler2.sa_handler=handler_SIGUSR2;
	
	sigaction(SIGUSR1,&handler1,NULL);
	sigaction(SIGUSR2,&handler2,NULL);

	PID_PERE=getpid();

	return( 0 );
}

/* le père doit appeler cette fonction lorsque tous les fils ont été créés */
int fin_clonage()
{
	int i=0;
	for(i=0;i<TAILLE;i++)
	{
		//Quand le père a fini de créer le nombre de ps qu'il veut, il envoit SIGUSR2 a tout ses enfants pour le signifier qu'ils n'ont plus a enregistrer la naissance de nouveau frère
		kill(tabPID[i],SIGUSR2);
	}
	free(tabPID);
	return( 0 );
}

/* fonction qui trouve les pids les <nb> frères du processus courant */
/* et les place dans le tableau <pids> qu'elle alloue */
/* cette fonction est blocante tant que le père n'a pas appelé fin_clonage() */
/* nb et pids sont des valeurs retournées par la fonction */
int pids_de_mes_freres( int *nb, pid_t **pids )
{	
	int i=0;
	for(i=0;i<TAILLE;i++)
	{
		if(tabPID[i] != getpid()) kill(tabPID[i],SIGUSR1);//J'envoie SIGUSR1 a tout mes frères pour me signifier ma naissance
	}
	
	
	kill(PID_PERE,SIGUSR2);//Je dis à mon père que j'ai fini de signifier ma naissance à tout mes frères
	
	while(continuerAttendreFrere) pause();//J'attend la naissance possible d'autre frère tant que mon père ne me dise le contraire par un SIGUSR2
	
	*pids=tabPID;
	*nb=TAILLE;
	
	return( 0 );
}

/* le père doit appeler cette fonction à chaque nouveau fils créé, avec son pid en paramètre */
int fils_suivant( pid_t p )
{
	if((TAILLE%MAX_PROC)==0)//Si on est arrivé à la fin du tableau, on réalloue le tout
	{
		tabPID=realloc(tabPID,TAILLE+MAX_PROC);
	}
	tabPID[TAILLE]=p;
	TAILLE++;
	if(pausePere) pause();//J'attend que mon nouveau fils me signifie qu'il a annoncé sa naissance à tout ses frères
	pausePere=1;//Si jamais il me l'a dit avant, le if d'avant est directement sauté, on remet les variables de controle à 1
	continuerAttendreFrere=1;//On remet aussi cet variable a 1 car lors d'un fork suivant, le ps fils aura besoin qu'elle soit à 1
	return( 0 );
}



void handler_SIGUSR1(int signum, siginfo_t * info, void * contexte)
{
	if((TAILLE % MAX_PROC)==0)//Si la taille du tableau est trop petit, on agrandit le tableau
	{
		tabPID=realloc(tabPID,TAILLE+MAX_PROC);
	}
	if(tabPID[TAILLE] != getpid()) tabPID[TAILLE]=info->si_pid;//Je met dans le tableau le pid du frère qui m'a signifier sa naissance
	TAILLE++;
}

/*
 * Si SIGUSR2 est lancé depuis le père aux fils, cette fonction permet de signifier aux fils qu'ils n'ont plus besoin d'attendre de nouveau frère
 * Si c'est le fils qui l'envoie au père, cette fonction permet de dire au père que le fils a signifier sa naissance à tout ses frères
 * */
void handler_SIGUSR2(int signum)
{
	continuerAttendreFrere=0;
	pausePere=0;
}
