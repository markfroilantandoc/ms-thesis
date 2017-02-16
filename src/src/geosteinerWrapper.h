#include "types.h"
#include "../ext/geosteiner/geosteiner.h"
#include <stdlib.h>

static void initArrays(int num_terminals, double **terminals, double **steiner_points, int **edges);
static void freeArrays(double **terminals, double **steiner_points, int **edges);
int esmt(int num_terminals, node *terminals, node **network);
void print_graph(int num_terminals, double *terminals, 
					int num_steiner_points, double *steiner_points,
					int num_edges, int *edges);