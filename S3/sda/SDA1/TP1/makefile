all:main main2

main:main.o files_fct.o
	gcc -Wall -o main main.o files_fct.o

main.o:main.c files_fct.h sorte.h
	gcc -c -Wall main.c

files_fct.o:files_fct.c files_fct.h sorte.h
	gcc -c -Wall files_fct.c


main2:main2.o files_mut.o
	gcc -Wall -o main2 main2.o files_mut.o

main2.o:main.c files_mut.h sorte.h
	gcc -c -Wall main2.c

files_mut.o:files_mut.c files_mut.h sorte.h
	gcc -c -Wall files_mut.c

clean:
	rm -r *.o main main2 html latex

doc:
	doxygen
