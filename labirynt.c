#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "labirynt.h"

labirynt init(int n) {
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
		l->maze[i] = calloc(n * n, sizeof(double));
		if (l->maze[i] == NULL) {
			free_labirynt(l);
			return NULL;
		}
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

void free_labirynt(labirynt l) {
	int i;
	if (l->obok != NULL) {
		for (i = 0; i < l->n * l->n; i++) {
			if (l->obok[i] == NULL)
				break;
			free(l->obok[i]);
		}
		free(l->obok);
	}
	if (l->maze != NULL) {
		for (i = 0; i < l->n * l->n; i++) {
			if (l->maze[i] != NULL)
				break;
			free(l->maze[i]);
		}
		free(l->maze);
	}
	if (l->visited != NULL)
		free(l->visited);
	if (l != NULL)
		free(l);
}

void ktore_obok(labirynt l) {
	int i;
	for (i = 0; i < l->n * l->n; i++) {
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

void losuj(labirynt l)
{
	int i, j, poz, tmp;
#ifdef DEBUG
    srand(DEBUG);
#else
    srand(time(NULL));
#endif
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

head init_stos() {
	head stos = malloc(sizeof(*stos));
	return stos;
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

void generuj(labirynt l) {
	int i, x, koniec, poz = l->n / 2;
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
					l->maze[poz][l->obok[poz][i]] = (double)rand() / RAND_MAX * 10;
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
}


void wypisz(labirynt l) {
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
			if (l->maze[i * l->n + j][i * l->n + j + 1] == 0 && l->maze[i * l->n + j + 1][i * l->n + j] == 0)
				printf("|   ");
			else
				printf("    ");
		}
		printf("|\n");
		if (i != l->n - 1) {
			for (j = 0; j < l->n; j++){
				if (l->maze[i * l->n + j][i * l->n + j + l->n] == 0 && l->maze[i * l->n + j + l->n][i * l->n + j] == 0)
					printf("+---");
				else
					printf("+   ");
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
	printf("  |-----Wyjscie\n");
}

int czy_liczba(char *liczba) {
	int i;
	for (i = 0; liczba[i]; i++)
		if (liczba[i] < '0' || liczba[i] > '9')
			return 0;
	return 1;
}
