#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS     2
#define MAX	1e8

/* 
 * But : utilisation des mutex 
 */

unsigned int global;
static pthread_mutex_t mutex;

void *increment_global(void *threadid)
{
  printf("Valeur initiale : %d\n", global);

   pthread_mutex_lock(&mutex); // entree en section critique
   while (global < MAX) {
	global++;
   }	
   pthread_mutex_unlock(&mutex); // sortie section critique

   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NB_THREADS];
   int i,
       rc;
   void *ret;

   global = 0;

   pthread_mutex_init (&mutex, NULL);
   for(i=0; i < NB_THREADS; i++){
       printf("Dans main : creation thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, increment_global, (void *)i);

      if (rc){
         printf("Erreur creation thread : %d\n", rc);
         exit(2);
      }
   }

   for (i = 0; i < NB_THREADS; ++i) {
        (void)pthread_join (threads[i], &ret);
   }

    printf("global : %d\n", global);   
    pthread_exit(NULL);
}
