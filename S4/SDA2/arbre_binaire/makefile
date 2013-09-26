CFLAGS=-g -Wall
IFLAGS=-Iinclude/ 
OPATH=obj/
BPATH=bin/
LDLIB=

vpath %.h include
vpath %.c src
vpath %.o obj
vpath arbre_binaire bin

all:arbre_binaire

arbre_binaire:main.o arbre_binaire.o liste_contigue.o
	gcc $(CFLAGS) -o arbre_binaire $(OPATH)main.o $(OPATH)arbre_binaire.o $(OPATH)liste_contigue.o
	mv $@ bin/

main.o:main.c arbre_binaire.h liste_contigue.h
arbre_binaire.o:arbre_binaire.h sorte_arbre.h liste_contigue.h
liste_contigue.o:sorte_arbre.h liste_contigue.h

%.o:%.c
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

clean:
	rm $(OPATH)* $(BPATH)*

directory:
	mkdir -p $(OPATH) $(BPATH)
