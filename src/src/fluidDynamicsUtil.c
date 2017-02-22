#include "fluidDynamicsUtil.h"

void static computeFlowDFS(int i, network *water_network, node *temp_junctions, int *visited, int **adjacency_matrix)
{
    int j;
    visited[i] = 1;

    for (j=0; j<water_network->node_count; j++) {
        if (!visited[j] && adjacency_matrix[i][j] == 1) {
            computeFlowDFS(j, water_network, temp_junctions, visited, adjacency_matrix);
        }
    }

    // process pipes connected to node
    printf("%d %lf\n", i, temp_junctions[i].flow);
    for (j=0; j<water_network->pipe_count; j++) {
        if (water_network->links[j].n1 == i) {
            water_network->links[j].flow += temp_junctions[i].flow;
            temp_junctions[water_network->links[j].n2].flow += temp_junctions[i].flow;
            temp_junctions[i].flow = 0;
        } else if (water_network->links[j].n2 == i) {
            water_network->links[j].flow += temp_junctions[i].flow;
            temp_junctions[water_network->links[j].n1].flow += temp_junctions[i].flow;
            temp_junctions[i].flow = 0;
        }
    }
}

void computeFlow(network *water_network, int **adjacency_matrix)
{
    int i;
    int *visited = NULL;
    node *temp_junctions;
    visited = (int *)malloc(water_network->node_count * sizeof(int));
    temp_junctions = (node *)malloc(water_network->node_count * sizeof(node));
    for (i=0; i<water_network->node_count; i++) {
        visited[i] = 0;
        temp_junctions[i] = water_network->junctions[i];
    }

    computeFlowDFS(0, water_network, temp_junctions, visited, adjacency_matrix);
    free(visited);
    free(temp_junctions);
}
