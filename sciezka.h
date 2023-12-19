#include "labirynt.h"

#ifndef SCIEZKA_H
#define SCIEZKA_H

typedef struct elem_sciez {
	int pole;
	double value;
	struct elem_sciez *next;
} *elem_sciez_pointer;

typedef struct sciezka {
	int first;
	struct elem_sciez *next;
} *sciezka_pointer;

sciezka_pointer init_sciezka(int);

sciezka_pointer szukaj(labirynt);

void wypisz_sciezka(sciezka_pointer);

#endif
