#ifndef STOS_H
#define STOS_H

typedef struct element {
	int n;
	struct element * next;
} *element_pointer;

typedef struct {
	element_pointer next;	
} *head;

head init_stos();

void free_stos(head);

void push(head, int);

int pop(head);

#endif
