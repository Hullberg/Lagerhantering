# Makefil för abstraktionsuppgiften
# Shortcuts:
CC = gcc
CFLAGS = -g -c -Wall -std=c99


# MAIN FILE MADDAFAKKA
lager: lagerhantering.c
	$(CC) $(CFLAGS) lagerhantering.c -o lager

