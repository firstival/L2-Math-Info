CFLAGS=-g -Wall
IFLAGS=-Iinclude/ 
OPATH=obj/
BPATH=bin/
LDLIB=

vpath %.h include
vpath %.c src
vpath %.o obj
vpath ProjetSDA2 bin

all:directory Exo1 Exo2 Exo3

Exo1:Exo1.o liste_chaine_simple.o listel_chaine_simple.o
	gcc $(CFLAGS) -o Exo1 $(OPATH)Exo1.o $(OPATH)liste_chaine_simple.o $(OPATH)listel_chaine_simple.o $(IFLAGS) $(LDLIB)
	@mv $@ $(BPATH)

Exo2:Exo2.o arbre_binaire.o liste_contigue_a.o liste_contigue.o
	gcc $(CFLAGS) -o Exo2 $(OPATH)Exo2.o $(OPATH)arbre_binaire.o $(OPATH)liste_contigue_a.o $(OPATH)liste_contigue.o $(IFLAGS) $(LDLIB)
	@mv $@ $(BPATH)

Exo3:Exo3.o liste_contigue.o liste_contigue_t.o
	gcc $(CFLAGS) -o Exo3 $(OPATH)Exo3.o $(OPATH)liste_contigue.o $(OPATH)liste_contigue_t.o $(IFLAGS) $(LDLIB)
	@mv $@ $(BPATH)

Exo1.o:liste_chaine_simple.h listel_chaine_simple.h
listel_chaine_simple.o:liste_chaine_simple.h
Exo2.o:arbre_binaire.h liste_contigue_a.h liste_contigue.h
arbre_binaire.o:sorte_arbre.h liste_contigue_a.h
liste_contigue_a.o:sorte_arbre.h
Exo3.o:liste_contigue.h liste_contigue_t.h sorte_tournoi_position.h
liste_contigue_t.o:sorte_tournoi_position.h

%.o:%.c %.h
	gcc -c $(CFLAGS) $< $(IFLAGS)
	@mv $@ $(OPATH)

clean:
	rm -f $(OPATH)* $(BPATH)*

directory:
	@mkdir -p $(OPATH) $(BPATH)

archive :clean 
	tar -f ProjetSDA2_Thomas_Kuntz.tar.gz -cvz src/* include/* makefile
