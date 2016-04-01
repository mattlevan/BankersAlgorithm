# Makefile for project

all: app cleanbuild

app: banker.c readfile.o
	gcc banker.c readfile.o -o banker.o -w

readfile.o: readfile.c
	gcc -c readfile.c -o readfile.o

clean: 
	rm -f banker.o

cleanbuild:
	rm -f readfile.o

