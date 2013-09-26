IPATH = include/
OPATH = obj/
BPATH = bin/
SPATH = src/
CFLAGS = -Wall -g
IFLAGS = -I$(IPATH) -I/usr/include/cairo
LDLIBS = -lcairo -lX11

vpath %.h include
vpath %.o obj
vpath %.c src
vpath main bin

all:main

main : main.o grille.o io.o jeu.o
	gcc $(CFLAGS) -o $(BPATH)main $(OPATH)main.o $(OPATH)grille.o $(OPATH)io.o $(OPATH)jeu.o $(LDLIBS)

grille.o :grille.c grille.h
io.o :io.c io.h grille.h
jeu.o :jeu.c jeu.h grille.h
main.o :main.c grille.h io.h

%.o: %.c
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

clean :
	rm $(BPATH)* $(OPATH)*

archive :
	tar -f jeudelavie.tar.gz -cvz $(SPATH)* $(IPATH)* makefile
