#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "labirynt.h"

int main(int argc, char **argv) {
	int n = argc > 1 ? atoi(argv[1]) : 5;
	int x = argc > 2 ? atoi(argv[2]) : time(NULL);
	labirynt l = init(n);
	ktore_obok(l);
	int i;
	losuj(l, x);
	for (i = 0; i < n * n; i++)
		printf("%d: %d %d %d %d\n", i, l->obok[i][0], l->obok[i][1], l->obok[i][2], l->obok[i][3]);
	wypisz(l);
	free_labirynt(l);
	return 0;
}
