
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main ( void )
{
printf ( "Bonjour " ) ;
if ( fork ( ) )
printf ( "Monsieur\n" ) ;
else
printf ( "Madame\n" ) ;
return 0 ;
} 
