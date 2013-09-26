#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
	static int t=0;
	int tmp=0;
	tmp=time(NULL);
	if((tmp-t)==0) exit(0);
	t=tmp;
	printf("\n%d %d\n",(rand()%6)+1,(rand()%6)+1);
}

int main(int argc,char ** argv)
{
	srand(time(NULL));
	struct sigaction action;
	action.sa_handler=handler;
	sigfillset(&action.sa_mask);
	sigaction(SIGINT,&action,NULL);
	printf("debut du programme\n");
	while(1) sleep(1);

	return 0;
}
