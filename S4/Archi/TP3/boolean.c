#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/******************************************************************************/
// Fonctions travaillant sur la table :
/******************************************************************************/

// Initialisation de la matrice :
void initialisation(uint8_t table[8][4])
{
	int i=0,j=0;
	for(i=0;i<2;i++)
	{
		for(j=i*4;j<4*(1+i);j++)table[j][0]=i;
	}
	for(i=0;i<4;i++)
	{
		for(j=i*2;j<2*(1+i);j++)table[j][1]=i%2;
	}
	j=0;
	for(i=0;i<8;i++)
	{
		table[i][2]=j;
		j=!j;
	}
	for(i=0;i<8;i++) table[i][3]=0;
}

// Affichage de la matrice :
void print(uint8_t table[8][4])
{
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<4;j++) printf("%d ",table[i][j]);
		printf("\n");
	}
}

// Modification de la table de vérité par une proposition :
void evalue( uint8_t(*proposition)(uint8_t, uint8_t, uint8_t), uint8_t table[8][4] )
{
	int i=0;
	for(i=0;i<8;i++) table[i][3]=proposition(table[i][0],table[i][1],table[i][2]);
}

// Affiche la forme normale disjonctive :
void disjonctive(uint8_t table[8][4])
{
	int i=0;
	int a=0;
	for(i=0;i<8;i++)
	{
		if(table[i][3])
		{
			if(a) printf("+");
			if(table[i][0]) printf("(A"); else printf("(!A");
			printf("*");
			if(table[i][1]) printf("B"); else printf("!B");
			printf("*");
			if(table[i][2]) printf("C)"); else printf("!C)");
			a=1;
		}
	}
	printf("\n");
}

// Affiche la forme normale conjonctive :
void conjonctive(uint8_t table[8][4])
{
	int i=0;
	int a=0;
	for(i=0;i<8;i++)
	{
		if(!table[i][3])
		{
			if(a) printf("*");
			if(table[i][0]) printf("(!A"); else printf("(A");
			printf("+");
			if(table[i][1]) printf("!B"); else printf("B");
			printf("+");
			if(table[i][2]) printf("!C)"); else printf("C)");
			a=1;
		}
	}
	printf("\n");
}


/******************************************************************************/
// Fonctions de proposition :
/******************************************************************************/

uint8_t p1(uint8_t a, uint8_t b, uint8_t c)
{
    return ((!a&&!b&&c)||(!a&&b&&!c)||(a&&!b&&!c)||(a&&!b&&c)||(a&&b&&!c));
}

uint8_t p2(uint8_t a, uint8_t b, uint8_t c)
{
    return ((a&&!b)||(b&&!c)||(!b&&c));
}

uint8_t enigme(uint8_t a, uint8_t b, uint8_t c)
{
    return ((a||b||c)&&(!a||(b||c||a))&&(b||!c)&&(c||!b)&&(!(b&&c)));
}

/******************************************************************************/
// Main :
/******************************************************************************/

int main(int argc, uint8_t* argv[])
{
    // Matrice pour table de vérité à 3 variables + résultat :
    // 2^3 lignes, 3+1 colonnes :
    uint8_t table[8][4];
    initialisation(table);

    // Début :
    printf("Initialisation :\n");
    print(table);

    // Affichage P1 :
    printf("\nP1 :\n");
    evalue(p1, table);
    print(table);
    printf("Forme disjonctive :\n");
    disjonctive(table);
    printf("Forme conjonctive :\n");
    conjonctive(table);

    // Affichage P2 :
    printf("\nP2 :\n");
    evalue(p2, table);
    print(table);

    // Affichage Énigme :
    printf("\nEnigme :\n");
    evalue(enigme, table);
    print(table);
    printf("Forme disjonctive :\n");
    disjonctive(table);
    printf("Forme conjonctive :\n");
    conjonctive(table);

    return 0;
}
