#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int * pid=NULL;
int n;
int p[2];

void handler_usr1(int signum,siginfo_t * info,void * context)
{
	static int pid_fils=0;
	static int num=0;
	num=(rand()%10);
	pid_fils=info->si_pid;
	write(p[1],&num,sizeof(int));
	kill(pid_fils,SIGUSR2);
}

void handler_usr2(int signum)
{
	static int i;
	read(p[0],&i,sizeof(int));
	printf("%d\n",i);
	sleep(5);
}

void handler_sigint(int signum)
{
	int i=0;
	close(p[0]);
	close(p[1]);
	for(i=0;i<n;i++)
	{
		kill(pid[i],SIGTERM);
		wait(NULL);
	}
	exit(0);
}

int main(int argc,char ** argv)
{
	if(argc < 2)
	{
		printf("Usage : exo5 n\n");
		exit(1);
	}
	srand(time(NULL));
	int pid_pere=getpid();
	n=atoi(argv[1]);
	pipe(p);

	pid=malloc(n*sizeof(int));

	struct sigaction action;

	action.sa_sigaction=handler_usr1;
	sigfillset(&action.sa_mask);
	action.sa_flags=SA_SIGINFO;
	sigaction(SIGUSR1,&action,NULL);

	action.sa_flags=0;
	action.sa_handler=handler_usr2;
	sigaction(SIGUSR2,&action,NULL);

	action.sa_handler=handler_sigint;
	sigaction(SIGINT,&action,NULL);

	int i=0;
	for(i=0;i<n;i++)
	{
		if((pid[i]=fork())==0) break;
	}
	
	if(pid[i]==0)
	{
		while(1) kill(pid_pere,SIGUSR1);
	}
	else //père
	{
		while(1) pause();
	}

	return 0;
}
