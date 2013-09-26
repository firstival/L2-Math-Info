#include <stdio.h>
#include <signal.h>

static void action( int s, siginfo_t *si, void *context )
{
	/* si->si_pid contient le pid du process ayant envoyÃ© le signal */
	printf( "J'ai reçu SIGUSR1 du processus de pid %d\n", si->si_pid );
}

int main()
{
	struct sigaction s;
	s.sa_sigaction = action;
	sigemptyset( &s.sa_mask );
	s.sa_flags = SA_SIGINFO;
	sigaction( SIGUSR1, &s, NULL );

	for(;;)
		;

	return(0);
}

