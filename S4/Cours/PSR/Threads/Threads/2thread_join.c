#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS     5

/*
 * But : Attente de terminaison des threads
 */


/**
 * Thread
 */

void *print(void *threadid)
{
   int param = (int)threadid;

   printf("\nBonjour, je suis le thread : %d\n\n", param);
   sleep(1);
   
   printf("Et je termine mon execution (thread %d)\n\n", param);
  //  return 9;
  pthread_exit(145);
}

/** 
 * Main
 */

int main (int argc, char *argv[])
{
   pthread_t threads[NB_THREADS];
   int i,
       rc;
   void *ret;

   for(i=0; i < NB_THREADS; i++){
      printf("Dans main : creation thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, print, (void *)i);

      if (rc){
         printf("Erreur creation thread : %d\n", rc);
         exit(2);
      }
   }

    for (i = 0; i < NB_THREADS; ++i) {
        (void)pthread_join(threads[i], &ret);
	printf("Pour le thread : %d, valeur renvoyée : %d\n", i, ret);
   }

   printf("Fin du main\n");
   pthread_exit(NULL);
}
