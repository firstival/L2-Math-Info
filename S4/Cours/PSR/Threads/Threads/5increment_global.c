#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS     	5
#define MAX		1e8

 /* Voir le temps d'exécution avec time, traitement plus long que version non threadé
  * var. globale en conflit d'accès
  */

unsigned int global;

void *increment_global(void *threadid)
{
   printf("Valeur initiale : %d\n", global);

   while (global < MAX) {
	global++;
   }	

   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NB_THREADS];
   int i,
       rc;
   void *ret;

   global = 0;

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
