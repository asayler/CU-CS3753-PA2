CC = gcc
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -Wall -Wextra

.PHONY: all clean

all: lookup

lookup: lookup.o
	$(CC) $(LFLAGS) $< -o $@

lookup.o: lookup.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f lookup *.o
	rm -f *~
