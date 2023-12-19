#include "stos.h"
#include <stdlib.h>

head init_stos() {
	head stos = malloc(sizeof(*stos));
    stos->next = NULL;
	return stos;
}

void free_stos(head stos) {
	element_pointer elem;
	while (stos->next != NULL) {
		elem = stos->next;
		stos->next = elem->next;
		free(elem);
	}
	free(stos);
}

void push(head stos, int a) {
	element_pointer next = malloc(sizeof(*next));
	next->n = a;
	next->next = stos->next;
	stos->next = next;
}

int pop(head stos) {
	int x;
	if (stos->next == NULL)
		return -1;
	element_pointer tmp = stos->next;
	stos->next = tmp->next;
	x = tmp->n;
	free(tmp);
	return x;
}
