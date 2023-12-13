#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "labirynt.h"

double **init(int n) {
	int i;
	double **labirynt = malloc(sizeof(*labirynt) * n * n);
	for (i = 0; i < n * n; i++)
		labirynt[i] = calloc(n * n, sizeof(double));
	return labirynt;
}

void wypisz(double **labirynt, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		if (i != n / 2)
			printf("+---");
		else
			printf("+   ");
	}
	printf("+\n");
	for (i = 0; i < n; i++) {
		printf("|   ");
		for (j = 0; j < n - 1; j++) {
			if (labirynt[i * n + j][i * n + j + 1] == 0 && labirynt[i * n + j + 1][i * n + j] == 0)
				printf("|   ");
			else
				printf("    ");
		}
		printf("|\n");
		if (i != n - 1) {
			for (j = 0; j < n; j++){
				if (labirynt[i * n + j][i * n + j + n] == 0 && labirynt[i * n + j + n][i * n + j] == 0)
					printf("+---");
				else
					printf("+   ");
			}
			printf("+\n");
		}
	}
	for (i = 0; i < n; i++) {
		if (i != n / 2)
			printf("+---");
		else
			printf("+   ");
	}
	printf("+\n");
}
