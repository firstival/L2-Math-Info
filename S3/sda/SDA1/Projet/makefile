CFLAGS = -O2
LDLIBS = -lX11


all:genlab cheminlab

genlab:mainc.o ensemble.o matrice.o constructeur.o graph.o sorte.o
	gcc -o genlab mainc.o ensemble.o matrice.o constructeur.o graph.o sorte.o $(LDLIBS)

cheminlab:mains.o ensemble.o matrice.o solveur.o graph.o sorte.o
	gcc -o cheminlab mains.o ensemble.o matrice.o solveur.o graph.o sorte.o $(LDLIBS)

mainc.o:mainc.c matrice.h constructeur.h
	gcc $(CFLAGS) -c mainc.c

mains.o:mains.c matrice.h solveur.h
	gcc $(CFLAGS) -c mains.c

constructeur.o:constructeur.c constructeur.h ensemble.h matrice.h graph.h sorte.h
	gcc $(CFLAGS) -c constructeur.c $(LDLIBS)

solveur.o:solveur.c solveur.h ensemble.h matrice.h graph.h sorte.h
	gcc $(CFLAGS) -c solveur.c $(LDLIBS)

ensemble.o:ensemble.c ensemble.h sorte.h
	gcc $(CFLAGS) -c ensemble.c

matrice.o:matrice.c matrice.h sorte.h
	gcc $(CFLAGS) -c matrice.c

sorte.o:sorte.c sorte.h
	gcc $(CFLAGS) -c sorte.c

graph.o:graph.c graph.h
	gcc $(CFLAGS) -c graph.c $(LDLIBS);

clean:
	rm *.o genlab cheminlab

doc:
	doxygen

archive :
	tar -f Labyrinthe.tar.gz -cvz *.c *.h makefile Doxyfile

