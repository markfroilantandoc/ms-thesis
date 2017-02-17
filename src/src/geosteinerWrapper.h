#include "types.h"
#include "../ext/geosteiner/geosteiner.h"
#include "mathUtil.h"
#include <stdlib.h>

static const double _default_elevation = 0;
static const double _default_diameter = 5;
static const double _default_flow = 0;

static void initArrays(int num_terminals, double **terminals, double **steiner_points, int **edges);
static void freeArrays(double **terminals, double **steiner_points, int **edges);
double esmt(int num_terminals, node *terminals, 
            int *node_count, node **network_nodes,
            int *pipe_count, pipe **network_pipes);