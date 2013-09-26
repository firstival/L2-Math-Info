#include "bases.c"
#include <stdlib.h>


/* Pointeur de fonction d'affichage d'un entier d'une certaine taille */
typedef void (*endian_print_t)(void* ptr, size_t size);

/* construit un uint32 à partir de quatre octets */
uint32_t make_uint32_t (uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3) 
{
    union {uint32_t i; uint8_t o[4];} v;
    v.o[0] = o0; v.o[1] = o1; v.o[2] = o2; v.o[3] = o3; 
    return v.i;
}

/* Affichage pour petit boutisme/little endian : */
void print_LE(void *ptr, size_t size)
{
	uint8_t * o=ptr+size;
	while(size>0)
	{
		base2(*o);
		o-=sizeof(char);
		size-=sizeof(char);
	}
}

/* Affichage pour grand boutisme/big endian : */
void print_BE(void *ptr, size_t size)
{
	uint8_t * o=ptr;
	while(size>0)
	{
		base2(*o);
		o+=sizeof(char);
		size-=sizeof(char);
	}
}

/* Choix de la bonne fonction d'affichage : */
endian_print_t endian()
{
   if(!(make_uint32_t(0,0,0,1) == 1)) return print_BE;
   else return print_LE;
}

/* Main : */
int main(int argc, char** argv)
{
    endian_print_t fun=endian();

    uint8_t a = 255;
    printf(" a = %d ", a);
    fun(&a, sizeof(a));

    uint32_t b = 0XF0F0F0F0;
    printf(" b = %X ", b);
    fun(&b, sizeof(b));

    float c = 333.333;
    printf(" c = %f ", c);
    fun(&c, sizeof(c));

    float d = -333.333;
    printf(" d = %f ", d);
    fun(&d, sizeof(d));

    return 0;
}

