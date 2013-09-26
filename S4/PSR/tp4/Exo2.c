#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 100


int t[MAX];
int temp[MAX];

typedef struct {int x;int y;} inter;



void fusion(int debut, int fin) {
  int i1,i2,i,mil;
  mil = (debut + fin)/2;
  i1 = debut;
  i2 = mil+1;
  i = debut;
  while((i1<=mil) && (i2<=fin)) {
    if(t[i1]<t[i2])
      {temp[i] = t[i1]; i++; i1++;}
    else
      {temp[i] = t[i2]; i++; i2++;}
  }
  while(i1<=mil) {temp[i] = t[i1]; i++; i1++;}
  while(i2<=fin) {temp[i] = t[i2]; i++; i2++;}
  for(i=debut;i<=fin;i++)
    t[i] = temp[i];
}

void * trifusion(void * arg)
{
	inter i=*(inter *)arg;
	if(i.y-i.x!=0)
	{
		if(i.y-i.x==1)
		{
			int tmp;
			if(t[i.x]>t[i.y])
			{
				tmp=t[i.x];
				t[i.x]=t[i.y];
				t[i.y]=tmp;
			}
		}
		else
		{
			pthread_t t1,t2;
			int tmp=(i.y+i.x)/2;
			inter i1={i.x,tmp};
			inter i2={tmp + 1,i.y};
			pthread_create(&t1,NULL,trifusion,(void *)&i1);
			pthread_create(&t2,NULL,trifusion,(void *)&i2);
			
			pthread_join(t1,NULL);
			pthread_join(t2,NULL);
			fusion(i.x,i.y);
		}
	}
	return NULL;		
}

void randomt()
{
	int i=0;
	for(i=0;i<MAX;i++) t[i]= rand() % (2*MAX);
}


int main()
{
	srand(time(NULL));
	randomt();
	inter it={0,MAX-1};
	int i=0;
	for(i=0;i<MAX;i++) printf("%d|",t[i]);
	printf("\n\n");
	trifusion((void *)&it);
	for(i=0;i<MAX;i++) printf("%d|",t[i]);
	printf("\n\n");
	return 0;
}
