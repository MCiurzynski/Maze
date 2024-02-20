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
	room maze; //Tablica przechowujaca labirynt
	int n; //Wiekość labiryntu
	int *visited; //Tablica informująca czy dany pokój został już odwiedzony przez algorymt
	int **obok; //Tabica przechowująca pokoje do których można się dostać z danego pokoju, maksymalnie 3 pozycje
} *labirynt; //Struktura przechowująca labirynt oraz dodatkowe informacje

#endif
