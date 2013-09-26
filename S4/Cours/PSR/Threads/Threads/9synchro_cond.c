#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


unsigned int v_in, v_out;
static pthread_cond_t cond_lance, cond_resultat;
static pthread_mutex_t mutex;


void *thread_entree_sortie(void *p)
{
  pthread_mutex_lock(&mutex);		// je prends le mutex
  printf("Entrez une valeur : ");
  scanf("%d", &v_in);

  pthread_cond_signal(&cond_lance);

  pthread_cond_wait(&cond_resultat,&mutex);	// attente de la fin du calcul, et libération du mutex

  printf("Le resultat du calcul est : %d\n", v_out);

  pthread_mutex_unlock(&mutex);		// je rends le mutex
  
  pthread_exit(NULL);
}

void *thread_calcul(void *p)
{
  pthread_mutex_lock(&mutex);		// je prends le mutex
  pthread_cond_wait(&cond_lance,&mutex);// mais j'attends qu'on me signale de faire un truc
  printf("On lance le calcul pour %d\n", v_in); 
  v_out = v_in*v_in;
  pthread_mutex_unlock(&mutex);		// je rends le mutex
  pthread_cond_signal(&cond_resultat);

  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[2];
   int i,
       rc;
   void *ret;

   pthread_cond_init(&cond_lance, NULL);
   pthread_cond_init(&cond_resultat, NULL);
   pthread_mutex_init(&mutex, NULL);

   // creation thread calcul
   rc = pthread_create(&threads[0], NULL, thread_calcul, NULL);

   if (rc){
         printf("Erreur creation thread : %d\n", rc);
         exit(2);
   }

   // creation thread saisie
   rc = pthread_create(&threads[1], NULL, thread_entree_sortie, NULL);

   if (rc){
         printf("Erreur creation thread : %d\n", rc);
         exit(2);
   }

   // attente fin des threads
   for (i = 0; i < 2; ++i) {
        (void)pthread_join (threads[i], &ret);
   }

    pthread_exit(NULL);
}
