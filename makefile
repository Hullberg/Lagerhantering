# Makefil för abstraktionsuppgiften
# Shortcuts:
CC = gcc
CFLAGS = -g -Wall -std=c99


# MAIN FILE
lager: lagerhantering.c
	$(CC) $(CFLAGS) lagerhantering.c -o lager

.PHONY: clean run tests

clean:
	rm -f lager *.o

run: lager
	./lager

lagerhantering.o: lagerhantering.c lagerhantering.h
	$(CC) $(CFLAGS) lagerhantering.c -c

tests: lagerhantering.o unittests.c
	$(CC) $(CFLAGS) unittests.c lagerhantering.o -o tests -lcunit

test : tests
	cat test.input | ./tests

