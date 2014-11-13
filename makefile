# Makefil för abstraktionsuppgiften
# Shortcuts:
CC = gcc
CFLAGS = -g -Wall -std=c99


# MAIN FILE
lager: lagerhantering.c
	$(CC) $(CFLAGS) lagerhantering.c -o lager

.PHONY: clean run

clean:
	rm -f lager

run: lager
	./lager
