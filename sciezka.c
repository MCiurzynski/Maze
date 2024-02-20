#include "sciezka.h"
#include "stos.h"
#include <stdlib.h>
#include <stdio.h>

sciezka_pointer init_sciezka(int start) { //Funkcja inicjująca strukturę ścieżki, przyjmuje jako argument początek ścieżki, zwraca strukture ścieżki
	sciezka_pointer sciezka = malloc(sizeof(*sciezka));
	if (sciezka == NULL)
		return NULL;
	sciezka->first = start;
	sciezka->next = NULL;
	return sciezka;
}

sciezka_pointer szukaj(labirynt l) { // Funkcja szukająca ścieżki rozwiązania labiryntu algorytmem dfs
				     // i przyjmująca jako argument strukturę labiryntu i zwracająca strukturę ścieżki
	int poz = l->n / 2, koniec = l->n * l->n - l->n + (l->n / 2);
	head stos = init_stos();
	if (stos == NULL)
		return NULL;
	elem_sciez_pointer element, tmp;
	if (stos == NULL)
		return NULL;
	while (poz != koniec) {
		while (l->maze[poz].n != 0) {
			l->maze[poz].n--;
			push(stos, poz);
			poz = (l->maze[poz].next[l->maze[poz].n]).who;
		}
		if (poz == koniec)
			break;
		poz = pop(stos);
	}
	free_stos(stos);
	sciezka_pointer sciezka = init_sciezka(l->n / 2);
	poz = l->n / 2;
	while (poz != koniec) {
		element = malloc(sizeof(*element));
		if (element == NULL) {
			if (sciezka->next == NULL) {
				free(sciezka);
				return NULL;
			}
			while (sciezka->next != NULL) {
				tmp = sciezka->next;
				sciezka->next = tmp->next;
				free(tmp);
			}
			free(sciezka);
			return NULL;
		}
		element->pole = (l->maze[poz].next[l->maze[poz].n]).who;
		element->value = (l->maze[poz].next[l->maze[poz].n]).value;
		element->next = NULL;
		poz = (l->maze[poz].next[l->maze[poz].n]).who;
		tmp = sciezka->next;
		if (sciezka->next == NULL) {
			sciezka->next = element;
		}
		else {
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = element;
		}
	}
    return sciezka;
}

void wypisz_sciezka(sciezka_pointer sciezka) { //Funkcja wypisująca ścieżkę rozwiązania labiryntu, jako argument dostaje ścieżkę
    elem_sciez_pointer tmp;
    int poz, przejscia = 0;
    double value = 0;
    printf("Skad Dokad Waga\n");
    while (sciezka->next != NULL) {
		poz = sciezka->first;
		tmp = sciezka->next;
		sciezka->next = tmp->next;
		sciezka->first = tmp->pole;
		printf("%4d %5d %lf\n", poz, tmp->pole, tmp->value);
		przejscia++;
		value += tmp->value;
		free(tmp);
	}
    free(sciezka);
    printf("Sciezka rozwiazujaca labirynt ma dlugosc: %d, i wage: %lf\n", przejscia, value);
}
