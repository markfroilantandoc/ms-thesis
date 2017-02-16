#include "types.h"
#include "../ext/geosteiner/geosteiner.h"
#include <stdlib.h>

static void initArrays(int num_terminals, double **terminals, double **steiner_points, int **edges);
static void freeArrays(double **terminals, double **steiner_points, int **edges);
double esmt(int num_terminals, node *terminals, 
            int *node_count, node **network_nodes,
            int *pipe_count, pipe **network_pipes);