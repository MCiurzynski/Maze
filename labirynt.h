#ifndef LABIRYNT_H
#define LABIRYNT_H

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

#endif
