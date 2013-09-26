
CC=gcc
SRCS=$(shell find . -name "*.c" -print)
TARGETS=$(foreach FILE, $(SRCS), $(shell basename $(FILE) .c))

all : $(TARGETS)

.c : 
	$(CC) -o $@ $< -lpthread

clean :
	rm -f $(TARGETS)

