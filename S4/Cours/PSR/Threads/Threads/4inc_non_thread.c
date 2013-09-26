#include <stdio.h>

#define MAX	1e8

unsigned int global;

main() {

	global = 0;
	while (global < MAX) {
		global++; 
	}
	printf("global : %d\n", global);
}
