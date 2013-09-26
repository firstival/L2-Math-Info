#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "exo1_freres.h"
#include "exo2_mutex.h"

/* programme de test de la bibliothèque exo1_freres et exo2_mutex */
/* ce programme est complet et ne doit pas être modifié */

/* crée n fils (n passé en argument), qui récupèrent les
 * pids de leurs frères puis incrémentent un compteur dans
 * un fichier protégé par un mutex.
 */

int main( int argc, char **argv )
{
	int n, i, fd;
	int compteur=0;
	if( argc != 2 || (n = atoi(argv[1]))<1 )
	{
		fprintf( stderr, "Usage: %s <nb_process>\n", argv[0] );
		exit( 1 );
	}

	fd = open("compteur", O_RDWR|O_CREAT|O_TRUNC, 0644);
	write( fd, &compteur, sizeof(int) );

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
			process_mutex_t mu;

			/* je récupère les pids de mes frères */
			pids_de_mes_freres( &nb, &pids );
			
			/* je crée un process_mutex */
			mutex_init( &mu, nb, pids );
			
			/* j'incrémente un compteur qui se trouve dans un fichier */
			/* protégé par une section critique */

			/* (si vous testez ce programme sans implémenter les
			 *  process_mutex, vous verrez que le compteur est mal
			 *  incrémenté, de différentes manières selon le nombre
			 *  de processus)
			 */
			for( j=0 ; j<1000 ; j++ )
			{
				
				
				mutex_lock( &mu ); /* début section critique */
				lseek( fd, 0, SEEK_SET );
				read( fd, &compteur, sizeof(int) );
				compteur++;
				lseek( fd, 0, SEEK_SET );
				write( fd, &compteur, sizeof(int) );
				mutex_unlock( &mu );  /* fin section critique */

			}
			close( fd );
			/*
			 * Signal la mort prochaine du processus à ses frères.
			 */
			for(j=0;j<nb;j++)
			{
				if(pids[j]!=-1)kill(pids[j],SIGUSR2);
			}
			
			free( pids );

			/* puis termine */
			exit( 0 );
		}
		fils_suivant( p );
	}

	fin_clonage();

	for( i=0 ; i<n ; i++ )
		wait( NULL );

	lseek( fd, 0, SEEK_SET );
	read( fd, &compteur, sizeof(int) );
	printf( "Compteur = %d\n", compteur );
	close( fd );

	return( 0 );
}
