#include "fluidDynamicsUtil.h"

void static computeFlowDFS(int i, network *waterNetwork, int *visited, int **adjacency_matrix)
{
    int j;
    // process pipe
    printf("%d\n", i);
    visited[i] = 1;

    for (j=0; j<waterNetwork->node_count; j++) {
        if (!visited[j] && adjacency_matrix[i][j] == 1) {
            computeFlowDFS(j, waterNetwork, visited, adjacency_matrix);
        }
    }
}

void computeFlow(network *waterNetwork, int **adjacency_matrix)
{
    int i;
    int *visited = NULL;
    visited = (int *)malloc(waterNetwork->node_count * sizeof(int));
    for (i=0; i<waterNetwork->node_count; i++) {
        visited[i] = 0;
    }

    computeFlowDFS(0, waterNetwork, visited, adjacency_matrix);
    free(visited);
}