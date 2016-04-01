# Makefile for project

all: app cleanbuild

app: banker.c readfile.o customer.o
	gcc banker.c readfile.o customer.o -o banker.o -w

readfile.o: readfile.c
	gcc -c readfile.c -o readfile.o

customer.o: customer.c 
	gcc -c customer.c -o customer.o

# manual clean of everything
clean: 
	rm -f banker.o
	rm -f readfile.o
	rm -f customer.o

# auto clean of only build items
cleanbuild:
	rm -f readfile.o
	rm -f customer.o

