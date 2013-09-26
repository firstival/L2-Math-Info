CFLAGS=-g -Wall
IFLAGS=-Iinclude/ 
OPATH=obj/
BPATH=bin/
LDLIB=

vpath %.h include
vpath %.c src
vpath %.o obj
vpath detv bin
vpath exempleTP bin

all:directory exempleTP detv

detv:detv.o ALineA-TP1.o ALineA-TP2.o
	gcc $(CFLAGS) -o detv $(OPATH)detv.o $(OPATH)ALineA-TP1.o $(OPATH)ALineA-TP2.o $(IFLAGS) $(LDLIB)
	mv $@ $(BPATH)
	
exempleTP:exempleTP.o ALineA-TP1.o ALineA-TP2.o
	gcc $(CFLAGS) -o exempleTP $(OPATH)exempleTP.o $(OPATH)ALineA-TP1.o $(OPATH)ALineA-TP2.o $(IFLAGS) $(LDLIB)
	mv $@ $(BPATH)

detv.o:ALineA-TP2.h
exempleTP.o:ALineA-TP2.h
ALineA-TP1.o:ALineA-TP1.h
ALineA-TP2.o:ALineA-TP2.h ALineA-TP1.h

%.o:%.c
	gcc $(CFLAGS) -c $< $(IFLAGS) $(LDLIB)
	mv $@ $(OPATH)

clean:
	rm $(OPATH)* $(BPATH)*

directory:
	mkdir -p $(OPATH) $(BPATH)

archive : 
	tar -f detv.tar.gz -cvz src/* include/* makefile output_* graph.gif readme
