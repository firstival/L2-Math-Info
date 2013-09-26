CFLAGS = -g -Wall
IFLAGS = -Iinclude 
OPATH = obj/

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

all : main

main : main.o grille.o io.o jeu.o sorte.o
	gcc $(CFLAGS) -o main $(OPATH)main.o $(OPATH)grille.o $(OPATH)io.o $(OPATH)jeu.o $(OPATH)sorte.o
	mv $@ bin/


grille.o : grille.h
io.o : io.h grille.h jeu.h sorte.h
jeu.o : jeu.h grille.h sorte.h
main.o : grille.h io.h jeu.h
sorte.o : sorte.h

%.o : %.c
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

clean : 
	rm obj/* bin/*

archive : 
	tar -f jeudelavie.tar.gz -cvz src/* include/* makefile readme
