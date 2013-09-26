CFLAGS=-g -Wall
IFLAGS=-Iinclude
OPATH=obj/
BPATH=bin/
LDLIB=

vpath %.h include
vpath %.c src
vpath %.o obj
vpath graphe_oriente bin

all:graphe_oriente

graphe_oriente:graphe_oriente.o main.o
	gcc $(CFLAGS) -o graphe_oriente $(OPATH)graphe_oriente.o $(OPATH)main.o $(IFLAGS)
	mv $@ $(BPATH)

graphe_oriente.o:graphe_oriente.h
main.o:graphe_oriente.h

%.o:%.c
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

clean:
	rm $(OPATH)* $(BPATH)*

directory:
	mkdir -p $(OPATH) $(BPATH)

archive : 
	tar -f graphe.gz -cvz src/* include/* makefile
