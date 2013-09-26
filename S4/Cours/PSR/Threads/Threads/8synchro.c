#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Exemple de synchronisation avec 2 mutex
// on preferera des solutions avec pthread_cond_wait et pthread_cond_signal

unsigned int v_in, v_out;
static pthread_mutex_t mutex_saisie, mutex_resultat;



void *thread_entree_sortie(void *threadid)
{

  printf("Entrez une valeur : ");
  scanf("%d", &v_in);

  pthread_mutex_unlock(&mutex_saisie);

  pthread_mutex_lock(&mutex_resultat);	// attente de la fin du calcul

  printf("Le resultat du calcul est : %d\n", v_out);
  
  pthread_exit(NULL);
}

void *thread_calcul(void *threadid) {
  pthread_mutex_lock(&mutex_saisie);
  printf("On lance le calcul pour %d\n", v_in); 
  v_out = v_in*v_in;
  pthread_mutex_unlock(&mutex_resultat);

  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[2];
   int i,
       rc;
   void *ret;

   pthread_mutex_init (&mutex_saisie, NULL);
   pthread_mutex_init (&mutex_resultat, NULL);

   pthread_mutex_lock(&mutex_saisie);
   pthread_mutex_lock(&mutex_resultat);

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
