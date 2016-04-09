# Makefile for project

all: app cleanbuild

app: banker.c customer.o
	gcc -pthread banker.c customer.o -o banker.o -w

customer.o: customer.c 
	gcc -c customer.c -o customer.o

# manual clean of everything
clean: 
	rm -f banker.o
	rm -f customer.o

# auto clean of only build items
cleanbuild: 
	rm -f customer.o

