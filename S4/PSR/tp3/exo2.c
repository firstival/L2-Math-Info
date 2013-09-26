#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int i=0;
int n=0;

void handler(int signum)
{
	i=n;
}

int main(int argc,char ** argv)
{
	struct sigaction action;
	action.sa_handler=handler;
	sigfillset(&action.sa_mask);
	sigaction(SIGINT,&action,NULL);

	printf("Veuillez entrer un nombre positif\n");
	scanf(" %d",&n);
	handler(0);
	
	do
	{
		sleep(1);
		printf("%d\n",i);
		i--;
	}
	while(i>=0);
	return 0;
}
