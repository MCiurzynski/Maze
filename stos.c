#include "stos.h"
#include <stdlib.h>

head init_stos() { //Funkcja inicjująca stos, zwraca głowę stosu
	head stos = malloc(sizeof(*stos));
	stos->next = NULL;
	return stos;
}

void free_stos(head stos) { //Funkcja zwalniająca pamięć zajmowaną przez stos, przyjmuje jako argument głowę stosu
	element_pointer elem;
	while (stos->next != NULL) {
		elem = stos->next;
		stos->next = elem->next;
		free(elem);
	}
	free(stos);
}

void push(head stos, int a) { //Funkcja push dokładająca element do stosu, przujmuje jako argumenty głowe stosu i liczbę którą ma dołożyć
	element_pointer next = malloc(sizeof(*next));
	next->n = a;
	next->next = stos->next;
	stos->next = next;
}

int pop(head stos) { //Funkcja zwracająca element stosu, przyjmuje jako argument głowe stosu
	int x;
	if (stos->next == NULL)
		return -1;
	element_pointer tmp = stos->next;
	stos->next = tmp->next;
	x = tmp->n;
	free(tmp);
	return x;
}
