#include <stdio.h>

/* Calcul x^n : */
long puiss(int x,int n) { return n==0?1:puiss(x,n-1)*x; }

int main(int argc, char** argv)
{
	int i=0;
	unsigned int x=1;
	long l,tmp;
	while(x!=0)
	{
		x*=2;
		i++;
	}
	l=puiss(2,i);
	printf("%d\n",(unsigned int)l);
	return 0;
}
