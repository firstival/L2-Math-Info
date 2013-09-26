#include <stdio.h>
#include <stdint.h>

/* retourne le n-ième (0 <= n <= 31) bit d'un float */
int nieme_bit(float f, int n)
{
    union {uint32_t i; float f;} v;
    v.f = f;
    return (v.i >> n) & 0x1;
}



