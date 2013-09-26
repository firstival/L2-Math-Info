CFLAGS=-g -Wall
IFLAGS=-Iinclude/ 
OPATH=obj/
BPATH=bin/
LDLIB=


vpath %.h include
vpath %.c src
vpath %.o obj
vpath shell bin

all:shell

shell:shell.o main.o liste_chaine_simple.o
	gcc $(CFLAGS) -o $@ $^ $(IFLAGS) $(LDLIB)
	mv $@ $(BPATH)

main.o:shell.h
shell.o:shell.h liste_chaine_simple.h
liste_chaine_simple.o:liste_chaine_simple.h
%.o:%.c
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)


clean:
	rm $(OPATH)* $(BPATH)*

directory:
	mkdir -p $(OPATH) $(BPATH)

archive : 
	tar -f shell.tar.gz -cvz src/* include/* makefile
