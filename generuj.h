#include "labirynt.h"

#ifndef GENERUJ_H
#define GENERUJ_H

labirynt init(int);

void free_labirynt(labirynt);

void ktore_obok(labirynt);

void losuj(labirynt);

void generuj(labirynt);

void wypisz_labirynt(labirynt);

void wypisz_labirynt_oznaczony(labirynt);

int czy_liczba(char*);

#endif
