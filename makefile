# Makefil för abstraktionsuppgiften
# Shortcuts:
CC = gcc
CFLAGS = -g -Wall -std=c99


# MAIN FILE
lager: lagerhantering.c
	$(CC) $(CFLAGS) lagerhantering.c -o lager

.PHONY: clean run test

clean:
	rm -f lager

run: lager
	./lager

lagerhantering.o: lagerhantering.c lagerhantering.h
	$(CC) $(CFLAGS) lagerhantering.c

tests: lagerhantering.o unittests.c
	$(CC) $(CFLAGS) unittests.c -o tests

test : tests
	./tests
