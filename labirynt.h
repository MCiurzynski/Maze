#ifndef LABIRYNT_H
#define LABIRYNT_H

typedef struct element {
	int n;
	struct element * next;
} *element_pointer;

typedef struct head {
	element_pointer next;	
} *head;

struct near {
	int who;
	double value;
};

typedef struct maze_room {
	int n;
	struct near next[3];
} *room;

typedef struct labirynt {
	room maze;
	int n;
	int *visited;
    int **obok;
} *labirynt;

labirynt init(int);

void free_labirynt(labirynt);

void ktore_obok(labirynt);

void losuj(labirynt);

head init_stos();

void push(head, int);

int pop(head);

void generuj(labirynt);

void wypisz(labirynt);

int czy_liczba(char*);

#endif
