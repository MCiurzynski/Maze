#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generuj.h"
#include "sciezka.h"

int main(int argc, char **argv) {
	if (argc > 2) {
		printf("Podano za duzo argumentow\n");
		return 5;
	}
	if (argc > 1) {
		if(czy_liczba(argv[1]) == 0) {
			printf("Nieprawidlowy argument\n");
			return 2;
		}
	}
	int n = argc > 1 ? atoi(argv[1]) : 5;
	if (n < 2 || n > 10) {
		printf("Nieprawidlowa liczba\n");
		return 3;
	}
	labirynt l = init(n);
	if (l == NULL) {
		printf("Nie udalo sie stworzyc labiryntu: ALLOCATION ERROR\n");
		return 1;
	}
	generuj(l);
	wypisz_labirynt(l);
	wypisz_labirynt_oznaczony(l);
	sciezka_pointer sciezka = szukaj(l);
	if (sciezka == NULL) {
		printf("Nie udalo sie zaalokowac pamieci na sciezke\n");
		free_labirynt(l);
		return 4;
	}
	wypisz_sciezka(sciezka);
	free_labirynt(l);
	return 0;
}
