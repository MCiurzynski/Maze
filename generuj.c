#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "stos.h"
#include "generuj.h"

labirynt init(int n) { //Funkcja inicjująca strukturę labiryntu, zwraca strukture, jeśli nie uda się zainicjować to zwraca NULL, jako argument przyjmuje szerokość labirytu
	int i;
	labirynt l = malloc(sizeof(*l));
	if (l == NULL)
		return NULL;
	l->n = n;
	l->visited = calloc(n * n, sizeof(int));
	if (l->visited == NULL) {
		free(l);
		return NULL;
	}
	l->maze = malloc(sizeof(*(l->maze)) * n * n);
	if (l->maze == NULL) {
		free_labirynt(l);
		return NULL;
	}
	for (i = 0; i < n * n; i++) {
		(l->maze[i]).n = 0;
		((l->maze[i]).next[0]).who = -1;
		((l->maze[i]).next[1]).who = -1;
		((l->maze[i]).next[2]).who = -1;
	}
	l->obok = malloc(sizeof(*(l->obok)) * n * n);
	if (l->obok == NULL) {
		free_labirynt(l);
		return NULL;
	}
	for (i = 0; i < n * n; i++) {
		l->obok[i] = malloc(4 * sizeof(int));
		if (l->obok[i] == NULL) {
			free_labirynt(l);
			return NULL;
		}
	}
	return l;
}

void free_labirynt(labirynt l) { //Funkcja zwalniająca pamięć zajmowaną przez labirynt, przyjmuje jako argument strukture labiryntu
	int i;
	if (l->obok != NULL) {
		for (i = 0; i < l->n * l->n; i++) {
			if (l->obok[i] == NULL)
				break;
			free(l->obok[i]);
		}
		free(l->obok);
	}
	if (l->maze != NULL)
		free(l->maze);
	if (l->visited != NULL)
		free(l->visited);
	if (l != NULL)
		free(l);
}

void ktore_obok(labirynt l) { //Funkcja zapisująca w strukturze labiryntu możliwe przejścia z danego 
			      //pomieszczenia labiryntu do innego pomieszczenia, przyjmuje jako argument strutkure labiryntu
	int i;
	for (i = 0; i < (l->n * l->n); i++) {
		if (i == 0 || i == l->n - 1 || i == (l->n * l->n - l->n) || i == l->n * l->n - 1) {
			if (i == 0) {
				l->obok[i][0] = 1;
				l->obok[i][1] = l->n;
				l->obok[i][2] = -1;
				l->obok[i][3] = -1;
			}
			if (i == l->n - 1) {
				l->obok[i][0] = i - 1;
				l->obok[i][1] = l->n * 2 - 1;
				l->obok[i][2] = -1;
				l->obok[i][3] = -1;
			}
			if (i == l->n * l->n - l->n) {
				l->obok[i][0] = l->n * l->n - (2 * l->n);
				l->obok[i][1] = l->n * l->n - l->n + 1;
				l->obok[i][2] = -1;
				l->obok[i][3] = -1;
			}
			if (i == l->n * l->n - 1) {
				l->obok[i][0] = l->n * l->n - l->n - 1;
				l->obok[i][1] = i - 1;
				l->obok[i][2] = -1;
				l->obok[i][3] = -1;
			}
			continue;
		}
		if (i > 0 && i < l->n - 1) {
			l->obok[i][0] = i - 1;
			l->obok[i][1] = i + 1;
			l->obok[i][2] = i + l->n;
			l->obok[i][3] = -1;
			continue;
		}
		if (i > l->n * l->n - l->n && i < l->n * l->n) {
			l->obok[i][0] = i - 1;
			l->obok[i][1] = i + 1;
			l->obok[i][2] = i - l->n;
			l->obok[i][3] = -1;
			continue;
		}
		if (i % l->n == 0) {
			l->obok[i][0] = i - l->n;
			l->obok[i][1] = i + l->n;
			l->obok[i][2] = i + 1;
			l->obok[i][3] = -1;
			continue;
		}
		if (i % l->n == l->n - 1) {
			l->obok[i][0] = i - l->n;
			l->obok[i][1] = i + l->n;
			l->obok[i][2] = i - 1;
			l->obok[i][3] = -1;
			continue;
		}
		l->obok[i][0] = i - l->n;
		l->obok[i][1] = i + l->n;
		l->obok[i][2] = i - 1;
		l->obok[i][3] = i + 1;
	}
}

void losuj(labirynt l) //Funcja losująca kolejne przejścia algorytmu generującego labirynt w strukturze labiryntu, przyjmuje jako argument tą strukture
{
	int i, j, poz, tmp;
	srand(time(NULL));
	for (i = 0; i < l->n * l->n; i++) {
		for (j = 0; j < 4; j++) {
			poz = ((double)rand()/RAND_MAX) * 4;
			if (j != poz) {
				tmp = l->obok[i][j];
				l->obok[i][j] = l->obok[i][poz];
				l->obok[i][poz] = tmp;
			}
		}
	}
}

void generuj(labirynt l) { //Funcja generująca labirynt w strukturze labiryntu, przyjmuje jako argument tą strukturę
	int i, x, koniec, poz = l->n / 2;;
	head stos = init_stos();
	ktore_obok(l);
	losuj(l);
	koniec = l->n * l->n - l->n + (l->n/2);
	push(stos, poz);
	l->visited[poz] = 1;
	while (stos->next != NULL) {
		x = 0;
		for (i = 0; i < 4; i++) {
			if (l->obok[poz][i] != -1) {
				if (l->visited[l->obok[poz][i]] == 0) {
					push(stos, poz);
					x = 1;
					l->visited[l->obok[poz][i]] = 1;
					((l->maze[poz]).next[(l->maze[poz]).n]).who = l->obok[poz][i];
					((l->maze[poz]).next[(l->maze[poz]).n]).value = (double)rand() / RAND_MAX * 10;
					(l->maze[poz]).n++;
					poz = l->obok[poz][i];
					break;
				}
			}
		}
		if (poz == koniec)
			poz = pop(stos);
		if (x == 0)
			poz = pop(stos);
	}
    free(stos);
}

void wypisz_labirynt(labirynt l) { //Funkcja rysująca labirynt bez oznaczeń pokoi, przyjmuje jako argument strukture labiryntu
	int i, j;
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  |-----Wejscie\n");
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  v\n");
	for (i = 0; i < l->n; i++) {
		if (i != l->n / 2)
			printf("+---");
		else
			printf("+   ");
	}
	printf("+\n");
	for (i = 0; i < l->n; i++) {
		printf("|   ");
		for (j = 0; j < l->n - 1; j++) {
			if (l->maze[i * l->n + j].next[0].who == (i * l->n + j + 1) || l->maze[i * l->n + j].next[1].who == (i * l->n + j + 1) || l->maze[i * l->n + j].next[2].who == (i * l->n + j + 1))
				printf("    ");
			else if (l->maze[i * l->n + j + 1].next[0].who == (i * l->n + j) || l->maze[i * l->n + j + 1].next[1].who == (i * l->n + j) || l->maze[i * l->n + j + 1].next[2].who == (i * l->n + j))
				printf("    ");
			else
				printf("|   ");
		}
		printf("|\n");
		if (i != l->n - 1) {
			for (j = 0; j < l->n; j++){
				if (l->maze[i * l->n + j].next[0].who == (i * l->n + j + l->n) || l->maze[i * l->n + j].next[1].who == (i * l->n + j + l->n) || l->maze[i * l->n + j].next[2].who == (i * l->n + j + l->n))
					printf("+   ");
				else if (l->maze[i * l->n + j + l->n].next[0].who == (i * l->n + j) || l->maze[i * l->n + j + l->n].next[1].who == (i * l->n + j) || l->maze[i * l->n + j + l->n].next[2].who == (i * l->n + j))
					printf("+   ");
				else
					printf("+---");
			}
			printf("+\n");
		}
	}
	for (i = 0; i < l->n; i++) {
		if (i != l->n / 2)
			printf("+---");
		else
			printf("+   ");
	}
	printf("+\n");
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  ^\n");
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  |-----Wyjscie\n\n");
}

void wypisz_labirynt_oznaczony(labirynt l) { //Funkcja rysuje labirynt w konsoli wraz z numerami pokoi
	int i, j;
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  |-----Wejscie\n");
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  v\n");
	for (i = 0; i < l->n; i++) {
		if (i != l->n / 2)
			printf("+---");
		else
			printf("+   ");
	}
	printf("+\n");
	for (i = 0; i < l->n; i++) {
		printf("|%2d ", i * l->n);
		for (j = 0; j < l->n - 1; j++) {
			if (l->maze[i * l->n + j].next[0].who == (i * l->n + j + 1) || l->maze[i * l->n + j].next[1].who == (i * l->n + j + 1) || l->maze[i * l->n + j].next[2].who == (i * l->n + j + 1))
				printf("%2d  ", i * l->n + j + 1);
			else if (l->maze[i * l->n + j + 1].next[0].who == (i * l->n + j) || l->maze[i * l->n + j + 1].next[1].who == (i * l->n + j) || l->maze[i * l->n + j + 1].next[2].who == (i * l->n + j))
				printf("%2d  ", i * l->n + j + 1);
			else
				printf("|%2d ", i * l->n + j + 1);
		}
		printf("|\n");
		if (i != l->n - 1) {
			for (j = 0; j < l->n; j++){
				if (l->maze[i * l->n + j].next[0].who == (i * l->n + j + l->n) || l->maze[i * l->n + j].next[1].who == (i * l->n + j + l->n) || l->maze[i * l->n + j].next[2].who == (i * l->n + j + l->n))
					printf("+   ");
				else if (l->maze[i * l->n + j + l->n].next[0].who == (i * l->n + j) || l->maze[i * l->n + j + l->n].next[1].who == (i * l->n + j) || l->maze[i * l->n + j + l->n].next[2].who == (i * l->n + j))
					printf("+   ");
				else
					printf("+---");
			}
			printf("+\n");
		}
	}
	for (i = 0; i < l->n; i++) {
		if (i != l->n / 2)
			printf("+---");
		else
			printf("+   ");
	}
	printf("+\n");
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  ^\n");
	for (i = 0; i < l->n / 2; i++)
		printf("    ");
	printf("  |-----Wyjscie\n\n");
}

int czy_liczba(char *liczba) { //Funkcja sprawdza czy podany argument jest liczba
	int i;
	for (i = 0; liczba[i]; i++)
		if (liczba[i] < '0' || liczba[i] > '9')
			return 0;
	return 1;
}
