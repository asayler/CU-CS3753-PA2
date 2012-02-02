CC = gcc
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -Wall -Wextra

.PHONY: all clean

all: lookup

lookup: lookup.o queue.o util.o
	$(CC) $(LFLAGS) $^ -o $@

lookup.o: lookup.c
	$(CC) $(CFLAGS) $<

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) $<

util.o: util.c util.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f lookup *.o
	rm -f *~
