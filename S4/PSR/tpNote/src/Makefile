CC = gcc
CFLAGS = -g -Wall
LDLIBS = -lpthread

all: exo1_essai exo2_essai

exo1_essai: exo1_freres.o
exo2_essai: exo1_freres.o exo2_mutex.o

exo1_freres.o: exo1_freres.h
exo2_mutex.o: exo2_mutex.h
exo1_essai.o: exo1_freres.h
exo2_essai.o: exo1_freres.h exo2_mutex.h

clean:
	/bin/rm -f *.o exo1_essai exo2_essai
