main:main.o alea.o io.o tri.o
	gcc -g -Wall -o main main.o alea.o io.o tri.o

main.o:main.c alea.h io.h tableau.h tri.h
	gcc -g -Wall -c main.c

alea.o:alea.c alea.h
	gcc -g -Wall -c alea.c

io.o:io.c io.h
	gcc -g -Wall -c io.c

tri.o:tri.c tri.h
	gcc -g -Wall -c tri.c

clean:
	rm *.o main
