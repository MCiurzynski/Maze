#ifndef LABIRYNT_H
#define LABIRYNT_H

struct near {
	int who;
	double value;
}; //Struktura przechowująca pojedyńcze przejście w labiryńcie

typedef struct maze_room {
	int n;
	struct near next[3];
} *room; //Struktura przechowująca przejścia z danego pokoju labiryntu do innego

typedef struct labirynt {
<<<<<<< HEAD
	double **maze;
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
=======
	room maze; //Tablica przechowujaca labirynt
	int n; //Wiekość labiryntu
	int *visited; //Tablica informująca czy dany pokój został już odwiedzony przez algorymt
	int **obok; //Tabica przechowująca pokoje do których można się dostać z danego pokoju, maksymalnie 3 pozycje
} *labirynt; //Struktura przechowująca labirynt oraz dodatkowe informacje
>>>>>>> memory

int czy_liczba(char *);

#endif
