#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void static computeFlowDFS(int i, network *waterNetwork, int *visited, int **adjacency_matrix);
void computeFlow(network *waterNetwork, int **adjacency_matrix);