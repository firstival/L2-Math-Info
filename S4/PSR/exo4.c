#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

typedef int S[2];

S * ouvrirpipe(int n)
{
	S* p=NULL;
	p=malloc(n*sizeof(S));
	for(n=n;n>0;n--) pipe(p[n-1]);
	return p;
}

S * fermerpipe(int n,int ** p,int k)
{
	int i=0;
	S * p2=malloc(sizeof(S));
	for(i=0;i<n;i++)
	{	
		if(k!=i || k!=(i-1))
		{
			close(p[i][0]);
			close(p[i][1]);
		}
	}
	close(p[k-1][1]);
	close(p[k][0]);
	p2[0]=p[k-1][0];
	p2[1]=p[k][1];
	return p2;
}

void closefreepipe(int n,int **p)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		close(p[i][0]);
		close(p[i][1]);
	}
	free(p);
}

int main (int argc,char **argv)
{
	int n=atoi(argv[1]);
	int i=0,pid=0;
	int ** p=ouvrirpipe(n),**p2=NULL;
	int a,b;
	for(i=1;i<=n;i++)
	{
		pid=fork();
		if(!pid) break;
	}
	if(!pid && i!=n)
	{
		printf("test\n");
		p2=fermerpipe(n,p,i);
		close(p2[0][1]);
		close(p2[1][0]);
		read(p2[0][0],&a,sizeof(int));
		printf("%d ",a);
		while(read(p2[0][0],&b,sizeof(int))>0) if(b%a != 0) write(p2[1][1],&b,sizeof(int));
		closefreepipe(n,p);
		free(p2);
		exit(0);
	}
	else if(!pid && i==n)
	{
		p2=fermerpipe(n,p,n-1);
		close(p2[0][1]);
		close(p2[0][0]);
		close(p2[1][1]);
		read(p2[1][0],&a,sizeof(int));
		close(p2[1][0]);
		closefreepipe(n,p);
		free(p2);
		printf("%d\n",a);
		exit(0);
	}
	else if(pid!=0)
	{
		a=2;
		while(a<=(n*n))
		{
			write(p[0][1],&a,sizeof(int));
			a++;
		}
		closefreepipe(n,p);
		for(i=1;i<=n;i++)
		{
			wait(&a);
			printf("%d\n", WTERMSIG(a));
		}
	}
	return 0;
}


