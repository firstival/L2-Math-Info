#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc,char ** argv)
{
	if(argc<3)
	{
		printf("Usage : matproc n m");
		exit(0);
	}
	int i=0;
	int n=atoi(argv[1]);
	int m=atoi(argv[2]);
	
	for(i=0;i<n && m>0;i++)
	{
		if(!fork())
		{
			i= -1;
			m--;
		}
	}

	for(i=0;i<n && m>0;i++) wait(NULL);
	return 0;
}
