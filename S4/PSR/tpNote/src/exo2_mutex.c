#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include "exo2_mutex.h"

int mutex=0;
int N;
pid_t * tab;

/* Initialisation d'un mutex. */
/* Tous les processus participant doivent appeler cette fonction */
/* (contrairement au fonctionnement de la bibliothèque pthread) */
/* paramètres :
 *  - pointeur sur une variable process_mutex_t allouée par l'appelant
 *  - nombre de processus participant
 *  - tableau de pids des processus participant
 * valeur de retour : 0 si succès
 */
int mutex_init( process_mutex_t *m, int nb, pid_t *pids )
{
	m->nb=nb;
	m->pids=pids;
	
	N=nb;
	tab=pids;
	
	struct sigaction handler1;
	struct sigaction handler2;
	
	sigemptyset(&handler1.sa_mask);
	sigemptyset(&handler2.sa_mask);
	
	handler2.sa_flags=SA_SIGINFO;
	
	handler2.sa_sigaction=handler_2;
	handler1.sa_handler=handler_1;
	sigaction(SIGUSR1,&handler1,NULL);
	sigaction(SIGUSR2,&handler2,NULL);
	
	int i=0;
	int min=0;
	if(nb>0)//Si on a plus d'un processus fils (et donc plus de 0 frère)
	{
		for(i=0;i<nb;i++) if(pids[i] < pids[min]) min=i;//On cherche le minimum parmi les frères
		if(getpid() < pids[min]) mutex=1;//Si on est plus petit que le minimum trouvé, on est alors le plus petit de TOUT les processus fils, on s'abroge alors le droit de se unlock soit meme
	}
	else mutex=1;
	return( 0 );
}

/* une fonction blocante tant qu'un autre processus possède le mutex */
/* paramètre :
 *  - pointeur sur une variable process_mutex_t initialisée par mutex_init
 * valeur de retour : 0 si succès
 */
int mutex_lock( process_mutex_t *m )
{
	while(!mutex)//Si on a pas le mutex, on attend de le recevoir
	{
		pause();
	}
	return 0;
}

/* une fonction qui rend le mutex */
/* paramètre :
 *  - pointeur sur une variable process_mutex_t initialisée par mutex_init
 * valeur de retour : 0 si succès
 */
int mutex_unlock( process_mutex_t *m )
{
	int i=0;
	for(i=0;i<m->nb;i++)
	{
		if(m->pids[i]!=-1)//Cas ou le frère n'est pas mort
		{
			if(kill(m->pids[i],SIGUSR1) == 0)//Si le frère accèpte le mutex, on le lui donne
			{
				mutex=0;
				break;
			}
		}
	}
	return 0;
}

void handler_1(int signum)
{
	mutex=1;
}

/*
 * Gère la mort d'un frère
 * */
void handler_2(int signum, siginfo_t * info, void * contexte)
{
	int i=0;
	for(i=0;i<N;i++) if(tab[i]==info->si_pid) tab[i]=-1;
}
