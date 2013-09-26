#include <unistd.h>
#include <time.h>

/* le type process_mutex_t est acessible à l'extérieur, mais
 * le contenu de la structure n'est accessible que dans le .c où
 * elle est déclarée
 */

/* la structure mutex, que vous pouvez modifier si vous le souhaitez */
struct _process_mutex
{
	int nb;      /* nombre de process participant */
	pid_t *pids; /* pids des process */
};

typedef struct _process_mutex process_mutex_t;

/* déclaration des fonctions */
int mutex_init( process_mutex_t *m, int nb, pid_t *pids );
int mutex_lock( process_mutex_t *m );
int mutex_unlock( process_mutex_t *m );


void handler_1(int signum);
void handler_2(int signum, siginfo_t * info, void * contexte);
