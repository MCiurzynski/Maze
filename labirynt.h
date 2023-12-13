#ifndef LABIRYNT_H
#define LABIRYNT_H

typedef struct element {
	int n;
	struct element * next;
} *element_pointer;

typedef struct head {
	element_pointer next;	
} head;

typedef struct labirynt {
	double **maze;
	int n;
	int *odwiedzone;
	head stos;
} labirynt;

double **init(int n);

void push(int n);

int pop();

void wypisz(double **labirynt, int n);

#endif
