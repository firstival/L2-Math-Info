CFLAGS=-g -Wall -O2
IFLAGS=-Iinclude/ 
OPATH=obj/
BPATH=bin/
LDLIB=

vpath %.h include
vpath %.c src
vpath %.o obj
vpath arbre_generaux bin

all:arbre_generaux

arbre_generaux:main.o arbre_generaux.o arbre_binaire.o liste_contigue.o
	gcc $(CFLAGS) -o arbre_generaux $(OPATH)main.o $(OPATH)arbre_binaire.o $(OPATH)arbre_generaux.o $(OPATH)liste_contigue.o
	mv $@ bin/

main.o:arbre_binaire.h
arbre_binaire.o:arbre_binaire.h liste_contigue.h sorte_arbre.h
liste_contigue.o:liste_contigue.h sorte_arbre.h
arbre_generaux.o:arbre_binaire.h arbre_generaux.h

%.o:%.c
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

clean:
	rm $(OPATH)* $(BPATH)*

directory:
	mkdir -p $(OPATH) $(BPATH)
