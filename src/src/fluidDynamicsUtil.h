#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double computeFlowLink(int index1, int index2, network *water_network, int **adjacency_matrix, int *visited);
// Computes flow of network.
// Assumptions: only single source and source is node 0.
void computeFlow(network *water_network, int **adjacency_matrix);