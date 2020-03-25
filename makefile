CC=gcc
CFLAGS = -Wall -g -std=c99

.PHONY: all clean

default: spath

all: spath

spath: assignment1b.c adjmat.c adjmat.h
	$(CC) $(CFLAGS) -o spath assignment1b.c adjmat.c adjmat.h

clean:
	rm spath; clear;
