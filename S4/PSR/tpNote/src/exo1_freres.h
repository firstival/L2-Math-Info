#include <unistd.h>
#include <signal.h>

void handler_SIGUSR1(int signum, siginfo_t * info, void * contexte);
void handler_SIGUSR2(int signum);

int init_freres();
int pids_de_mes_freres( int *nb, pid_t **pids );
int fils_suivant( pid_t p );
int fin_clonage( void );
