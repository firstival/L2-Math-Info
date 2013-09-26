main: main.o grille.o io.o jeu.o
	gcc -Wall -g -o main main.o grille.o io.o jeu.o
	
main.o:main.c grille.h io.h jeu.h
	gcc -Wall -g -c main.c

grille.o:grille.c grille.h
	gcc -Wall -g -c grille.c
	
io.o:io.c io.h grille.h jeu.h
	gcc -Wall -g -c io.c
	
jeu.o:jeu.c jeu.h grille.h
	gcc -Wall -g -c jeu.c
	
clean:
	rm main *.o *.tar
	
doc:
	doxygen
	
archive:
	tar -cz *.c *.h makefile -f jeudelavie.tar.gz
