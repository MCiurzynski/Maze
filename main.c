#include <stdio.h>
#include <stdlib.h>
#include "labirynt.h"

int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	double **labirynt = init(n);
	int i, j;
	for (i = 0; i < n * n; i++) {
		for (j = 0; j < n * n; j++)
			labirynt[i][j] =  rand() % 2;
	}
	wypisz(labirynt, n);
	return 0;
}
