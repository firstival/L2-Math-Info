#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS     2
#define MAX	1e8

void *increment_local(void *threadid)
{
   unsigned int local=0;

   while (local < MAX/NB_THREADS) {
	local++;
   }	

   printf("Fini pour : %d, valeur global : %d\n", (int)threadid, local);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NB_THREADS];
   int i,
       rc;
   void *ret;


   for(i=0; i < NB_THREADS; i++){
       printf("Dans main : creation thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, increment_local, (void *)i);

      if (rc){
         printf("Erreur creation thread : %d\n", rc);
         exit(2);
      }
   }

   for (i = 0; i < NB_THREADS; ++i) {
        (void)pthread_join (threads[i], &ret);
   }

    pthread_exit(NULL);
}
