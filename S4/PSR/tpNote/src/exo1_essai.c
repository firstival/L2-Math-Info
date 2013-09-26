#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "exo1_freres.h"

/* programme de test de la bibliothèque exo1_freres */
/* ce programme est complet et ne doit pas être modifié */

/* crée n fils (n passé en argument), qui récupèrent les
 * pids de leurs frères puis les affichent.
 */

int main( int argc, char **argv )
{
	int n, i;
	if( argc != 2 || (n = atoi(argv[1]))<1 )
	{
		fprintf( stderr, "Usage: %s <nb_process>\n", argv[0] );
		exit( 1 );
	}
	init_freres();
	for( i=0 ; i<n ; i++ )
	{
		pid_t p;
		p = fork();
		if( p<0 )
		{
			perror( "cannot fork" );
			exit( 2 );
		}
		if( p == 0 )
		{
			/* je suis le fils */
			int nb, j;
			pid_t *pids;

			pids_de_mes_freres( &nb, &pids );

			/* affiche les pids des frères */
			printf( "Je suis %d. Mes frères sont : [%d", getpid(), pids[0] );
			for( j=1 ; j<nb ; j++ )
				printf( ", %d", pids[j] );
			printf( "]\n" );
			free(pids);
			/* puis termine */
			exit( 0 );
		}
		printf( "Père: création du fils %d\n", p );
		fils_suivant( p );
	}

	fin_clonage();

	printf( "Père: attente fin des fils\n" );
	for( i=0 ; i<n ; i++ )
		wait( NULL );

	return( 0 );
}
