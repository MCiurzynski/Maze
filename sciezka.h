#include "labirynt.h"

#ifndef SCIEZKA_H
#define SCIEZKA_H

typedef struct elem_sciez {
	int pole;
	double value;
	struct elem_sciez *next;
} *elem_sciez_pointer; //Struktura przechowująca element ścieżki rozwiązującej labirynt

typedef struct sciezka {
	int first;
	struct elem_sciez *next;
} *sciezka_pointer; //Struktura przechowująca ścieżkę rozwiązania labiryntu, oparta na stosie

sciezka_pointer init_sciezka(int);

void sort(labirynt);

sciezka_pointer szukaj(labirynt);

void wypisz_sciezka(sciezka_pointer);

#endif
