#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void static computeFlowDFS(int i, network *water_network, node *temp_junctions, int *visited, int **adjacency_matrix);
void computeFlow(network *water_network, int **adjacency_matrix);
double computeFlowLink(int index1, int index2, network *water_network, int **adjacency_matrix, int *visited);
void computeFlowNew(network *water_network, int **adjacency_matrix);