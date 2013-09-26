
CFLAGS = -O2 -Wall
LDLIBS = -L /usr/X11R6/lib -lX11

ALL=julia julia2 mandel gvie

all: $(ALL)

$(ALL): graph.o

clean:
	/bin/rm $(ALL)
