#include <stdio.h>      // Entrée / Sortie standard
#include <stdint.h>     // Entiers standard
#include <stdlib.h>


int d2c (int n)
{
    if(0<=n && n<10)
        return '0'+n;
    else    if (n < 36)
        return 'A'+ (n-10);
    else return '?';
}


void base2(uint8_t entier)
{
	int i=0;
	char tab[8];
	for(i=0;i<8;i++)
	{
		tab[i]=entier%2;
		entier/=2;
	}
	for(i=0;i<8;i++) printf("%d",tab[7-i]);
}

void base8(uint8_t entier)
{
	int i=0;
	char tab[3];
	for(i=0;i<3;i++)
	{
		tab[i]=entier%8;
		entier/=8;
	}
	for(i=0;i<3;i++) printf("%d",tab[2-i]);
}

void base16(uint8_t entier)
{
	int i=0;
	char tab[2];
	for(i=0;i<2;i++)
	{
		tab[i]=entier%16;
		entier/=16;
	}
	for(i=0;i<2;i++) printf("%c", d2c(tab[1-i]));
}

void basen(uint8_t entier, uint8_t base)
{
    int i=0;
    int t=256,b=0;
    while(t>1)
    {
		t/=base;
		b++;
	} 
    char * tab=malloc(base*sizeof(char));
    for(i=0;i<b;i++)
    {
		tab[i]=entier%base;
		entier/=base;
	}
	for(i=0;i<b;i++) printf("%c",d2c(tab[b-i-1]));
}
