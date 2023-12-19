#include "sciezka.h"
#include "stos.h"
#include <stdlib.h>
#include <stdio.h>

sciezka_pointer init_sciezka(int start) {
	sciezka_pointer sciezka = malloc(sizeof(*sciezka));
	if (sciezka == NULL)
		return NULL;
	sciezka->first = start;
	sciezka->next = NULL;
	return sciezka;
}

void sort(labirynt l) {
	int i, twho;
	double tvalue;
	for (i = 0; i < l->n * l->n; i++) {
		if (l->maze[i].next[0].who > l->maze[i].next[1].who && l->maze[i].n > 1) {
			twho = l->maze[i].next[0].who;
			tvalue = l->maze[i].next[0].value;
			l->maze[i].next[0].who = l->maze[i].next[1].who;
			l->maze[i].next[0].value = l->maze[i].next[1].value;
			l->maze[i].next[1].who = twho;
			l->maze[i].next[1].value = tvalue;
		}
		if (l->maze[i].next[1].who > l->maze[i].next[2].who && l->maze[i].n > 2) {
			twho = l->maze[i].next[1].who;
			tvalue = l->maze[i].next[1].value;
			l->maze[i].next[1].who = l->maze[i].next[2].who;
			l->maze[i].next[1].value = l->maze[i].next[2].value;
			l->maze[i].next[2].who = twho;
			l->maze[i].next[2].value = tvalue;
		}
	}
}

sciezka_pointer szukaj(labirynt l) {
	int poz = l->n / 2, koniec = l->n * l->n - l->n + (l->n / 2);
	head stos = init_stos();
	sort(l);
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

void wypisz_sciezka(sciezka_pointer sciezka) {
    elem_sciez_pointer tmp;
    int poz, przejscia = 0;
    double value;
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
    printf("Sciezka rozwiazujaca labirynt ma dlugosc: %d, i wage: %g\n", przejscia, value);
}
