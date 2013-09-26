#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int valeur_courante=0;
int indice_courant=0;
int i=1;

int max_i=1;
int max_indice=0;
int altitude=0;

struct sigaction action;


void handler_sigint2(int signum)
{
	printf("\n%d %d %d\n",max_i,altitude,max_indice);
	exit(0);
}

void handler_sigint1(int signum)
{
	printf("\n%d %d %d\n",max_i,altitude,max_indice);
	action.sa_handler=handler_sigint2;
	sigaction(SIGINT,&action,NULL);
	alarm(2);
}

void handler_tstp(int signum)
{
	printf("\n%d %d %d\n",i,indice_courant,valeur_courante);
}

void handler_sigalrm(int signum)
{
	action.sa_handler=handler_sigint1;
	sigaction(SIGINT,&action,NULL);
}


void syracuse()
{
	valeur_courante=i;
	indice_courant=0;
	while(valeur_courante != 1)
	{
		usleep(5000);
		if(valeur_courante > altitude)
		{
			altitude=valeur_courante;
			max_i=i;
			max_indice=indice_courant;
		}
		indice_courant++;
		if((valeur_courante % 2)==0) valeur_courante/=2;
		else valeur_courante = valeur_courante*3 +1;
	}
}

int main(int argc,char ** argv)
{
	action.sa_handler=handler_tstp;
	sigfillset(&action.sa_mask);
	sigaction(SIGTSTP,&action,NULL);

	action.sa_handler=handler_sigint1;
	sigaction(SIGINT,&action,NULL);

	action.sa_handler=handler_sigalrm;
	sigaction(SIGALRM,&action,NULL);

	while(1)
	{
		syracuse();
		usleep(5000);
		i++;
	}
	return 0;
}
