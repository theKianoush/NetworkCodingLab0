# Makefile for client and server

CC = gcc
OBJCS = client0.c
OBJCSS = server0.c

CFLAGS =  -g -Wall
# setup for system
nLIBS =

all: client0 server0

client0: $(OBJCS)
	$(CC) $(CFLAGS) -o $@ $(OBJCS) $(LIBS)

server0: $(OBJCSS)
	$(CC) $(CFLAGS) -o $@ $(OBJCSS) $(LIBS)


clean:
	rm client0 server0
