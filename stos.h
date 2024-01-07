#ifndef STOS_H
#define STOS_H

typedef struct element {
	int n;
	struct element * next;
} *element_pointer; // Struktura elementu stosu

typedef struct {
	element_pointer next;
} *head; // Struktura głowy stosu, czyli jego początek

head init_stos();

void free_stos(head);

void push(head, int);

int pop(head);

#endif
