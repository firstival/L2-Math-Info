CFLAGS=-g -Wall
IFLAGS=-Iinclude/ 
OPATH=obj/
BPATH=bin/
LDLIB=-lm

vpath %.h include
vpath %.c src
vpath %.o obj
vpath valpropreQR bin

all:directory valpropreQR valpropreGNUplot

valpropreGNUplot:main_gnuplot.o valeur_propre.o decomposition_QR.o ALineA-TP1.o ALineA-TP2.o
	gcc -o valpropreGNUplot $(OPATH)main_gnuplot.o $(OPATH)valeur_propre.o $(OPATH)decomposition_QR.o $(OPATH)ALineA-TP1.o $(OPATH)ALineA-TP2.o $(CFLAGS) $(IFLAGS) $(LDLIB)
	@mv $@ $(BPATH)

valpropreQR:main.o valeur_propre.o decomposition_QR.o ALineA-TP1.o ALineA-TP2.o
	gcc -o valpropreQR $(OPATH)main.o $(OPATH)valeur_propre.o $(OPATH)decomposition_QR.o $(OPATH)ALineA-TP1.o $(OPATH)ALineA-TP2.o $(CFLAGS) $(IFLAGS) $(LDLIB)
	@mv $@ $(BPATH)


main.o:ALineA-TP1.h valeur_propre.h
main_gnuplot.o:ALineA-TP1.h valeur_propre.h
valeur_propre.o:valeur_propre.h decomposition_QR.h ALineA-TP2.h
decomposition_QR.o:decomposition_QR.h ALineA-TP2.h
ALineA-TP1.o:ALineA-TP1.h
ALineA-TP2.o:ALineA-TP2.h ALineA-TP1.h

%.o:%.c
	gcc $(CFLAGS) -c $< $(IFLAGS) $(LDLIB)
	@mv $@ $(OPATH)

clean:
	rm -f $(OPATH)* $(BPATH)*

directory:
	@mkdir -p $(OPATH) $(BPATH)

archive : 
	tar -f valpropreQR_Kuntz_Thomas.tar.gz -cvz src/* include/* makefile GenererFichier.sh matrice_* README gnuplot_8x8
