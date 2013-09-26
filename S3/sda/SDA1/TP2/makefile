all:main3 main4

main3:main3.o files_ch.o
	gcc -Wall -g -o main3 main3.o files_ch.o

main3.o:main3.c files_ch.h sorte.h
	gcc -Wall -g -c main3.c
	
files_ch.o:files_ch.c files_ch.h sorte.h
	gcc -Wall -g -c files_ch.c

main4:main4.o files_chop.o
	gcc -Wall -g -o main4 main4.o files_chop.o

main4.o:main4.c files_chop.h sorte.h
	gcc -Wall -g -c main4.c
	
files_chop.o:files_chop.c files_chop.h sorte.h
	gcc -Wall -g -c files_chop.c	

clean:
	rm *.o main3 main4

doc:
	doxygen
	
archive:
	tar -cz *.c *.h makefile resultat -f sda1_tp2.tar.gz
