CC=gcc
CFLAGS=-g -O1 -Wall
LDLIBS=-lpthread

all: client server

client: client.c csapp.h csapp.c
server: server.c csapp.h csapp.c

clean:
	rm -f *.o *~ *.exe client server csapp.o

