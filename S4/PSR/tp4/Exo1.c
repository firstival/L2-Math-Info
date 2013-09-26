#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



//Cette fonction doit recevoir comme argument
//le nom donné au thread
void *ma_nouvelle_sequence_control (void * arg)
{
int i;
for (i = 0 ; i < 10 ; i++) {
printf ("Thread %s: %d\n", (char*)arg, i);
sleep (1);
}
pthread_exit (0);
}


int main()
{
	pthread_t t1,t2,t3;
	
	pthread_create(&t1,NULL,ma_nouvelle_sequence_control,(void *)"n°1");
	pthread_create(&t2,NULL,ma_nouvelle_sequence_control,(void *)"n°2");
	pthread_create(&t3,NULL,ma_nouvelle_sequence_control,(void *)"n°3");
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	
	
	return 0;
}
