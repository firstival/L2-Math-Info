#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_THREADS     1

/*
 * But : Passage de plusieurs paramètres dans une structure
 * Attention : programme éronné, on ne retourne pas l'@ d'une var. locale, il faut faire un malloc
 */


typedef struct {
	int a;
	float b;
} Pipo;

/**
 * Thread
 */

void *print(void *threadid)
{
     Pipo p = *((Pipo *)threadid);
 //  Pipo *p = (Pipo *)malloc (sizeof( Pipo)); // 


 //  *p = *((Pipo *)threadid);
   printf("\nValeurs reçues : (%d, %f)\n\n", p.a, p.b);
 //  printf("\nValeurs reçues : (%d, %f)\n\n", p->a, p->b);
   
   p->a++;
   p->b++;
 //  printf("Je retourne : (%d, %f)\n\n",p->a, p->b);
   printf("Je retourne : (%d, %f)\n\n",p.a, p.b);

   return &p;
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
   Pipo p;
   p.a = 5;
   p.b = 2.71;

   for(i=0; i < NB_THREADS; i++){
      printf("Dans main : creation thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, print, (void *)&p);

      if (rc){
         printf("Erreur creation thread : %d\n", rc);
         exit(2);
      }
   }

    for (i = 0; i < NB_THREADS; ++i) {
        (void)pthread_join(threads[i], &ret);
	  p = *((Pipo *)ret);
	  printf("Pour le thread : %d, valeur renvoyée : %d %f\n", i, p.a, p.b);
   }

   printf("Fin du main\n");
   pthread_exit(NULL);
}
