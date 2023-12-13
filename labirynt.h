#ifndef LABIRYNT_H
#define LABIRYNT_H

typedef struct element {
	int n;
	struct element * next;
} *element_pointer;

typedef struct head {
	element_pointer next;	
} *head;

typedef struct labirynt {
	double **maze;
	int n;
	int *visited;
    int **obok;
} *labirynt;

labirynt init(int);

void free_labirynt(labirynt);

void ktore_obok(labirynt);

void losuj(labirynt, int);

void push(int);

int pop();

void wypisz(labirynt);

#endif
