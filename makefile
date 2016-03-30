# Makefile for project

all: app

app: banker.c
	gcc banker.c -o banker.o -w

clean: 
	rm -f banker.o
