#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "labirynt.h"

int main(int argc, char **argv) {
	if (argc > 1) {
		if(czy_liczba(argv[1]) == 0) {
			printf("Nieprawidlowy argument\n");
			return 2;
		}
	}
	int n = argc > 1 ? atoi(argv[1]) : 5;
#ifndef MORE
	if (n < 1 || n > 10) {
		printf("Nieprawidlowa liczba\n");
		return 3;
	}
#else
	if (n == 0) {
		printf("Nieprawidlowa liczba\n");
		return 3;
	}
#endif
	labirynt l = init(n);
	if (l == NULL) {
		printf("Nie udalo sie stworzyc labiryntu: ALLOCATION ERROR\n");
		return 1;
	}
    generuj(l);
	wypisz(l);
	free_labirynt(l);
	return 0;
}
