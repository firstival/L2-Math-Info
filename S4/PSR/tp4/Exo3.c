#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3
#define INCONNU -1

int fibtab[N]={0,1};

void * fibo1(void * arg)
{
	int n=(int)arg;
	if(n<2) pthread_exit(arg);
	else
	{
		void * x,*y,*tmp1=n-1,*tmp2=n-2;
		pthread_t t1,t2;
		pthread_create(&t1,NULL,fibo1,tmp1);
		pthread_create(&t2,NULL,fibo1,tmp2);
		
		pthread_join(t1,&x);
		pthread_join(t2,&y);
		
		tmp1=(int)x+(int)y;
		
		pthread_exit(tmp1);
	}
}


void * fibo2(void * arg)
{
	int n=(int)arg;
	if(fibtab[n]==INCONNU)
	{
		void *tmp1=n-1,*tmp2=n-2;
		pthread_t t1,t2;
		pthread_create(&t1,NULL,fibo2,tmp1);
		pthread_join(t1,NULL);
		pthread_create(&t2,NULL,fibo2,tmp2);
		pthread_join(t2,NULL);
		
		fibtab[n]=fibtab[n-1]+fibtab[n-2];
	}
	pthread_exit(0);
}

void initTab(int n)
{
	int i=0;
	for(i=0;i<n;i++)fibtab[i]=INCONNU;
	fibtab[0]=0;
	fibtab[1]=1;
}
	

int main()
{
	initTab(N);
	pthread_t t;
	pthread_create(&t,NULL,fibo2,(void *)N);
	pthread_join(t,NULL);
	printf("Fibonacci de %d : %d\n",N,fibtab[N]);
	
	return 0;
}
