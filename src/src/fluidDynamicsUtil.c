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

double computeFlowLink(int index1, int index2, network *water_network, int **adjacency_matrix, int *visited)
{
    int i, index, flag = 1;
    //printf("%d %d\n", index1, index2);
    if (index2 < index1) {
        flag = -1;
    }
    for (i=0; i<water_network->pipe_count; i++) {
        if ((water_network->links[i].n1 == index1 && water_network->links[i].n2 == index2) ||
            (water_network->links[i].n2 == index1 && water_network->links[i].n1 == index2)) {
            index = i;
            break;
        }
    }
    visited[i] = 1;
    for (i=0; i<water_network->pipe_count; i++) {
        if (water_network->links[i].n1 == index2 && !visited[i]) {
            water_network->links[index].flow -= computeFlowLink(index2, water_network->links[i].n2, water_network, adjacency_matrix, visited);
        } else if (water_network->links[i].n2 == index2 && !visited[i]) {
            water_network->links[index].flow += computeFlowLink(index2, water_network->links[i].n1, water_network, adjacency_matrix, visited);
        }
    }
    water_network->links[index].flow -= water_network->junctions[index1].flow;
    water_network->links[index].flow += water_network->junctions[index2].flow;
    printf("\t %d %d\n", index1, index2);
    return water_network->links[index].flow;
}

void computeFlowNew(network *water_network, int **adjacency_matrix)
{
    int i;
    int *visited = NULL;
    visited = (int *)malloc(water_network->node_count * sizeof(int));
    for (i=0; i<water_network->node_count; i++) {
        visited[i] = 0;
    }
    computeFlowLink(0, 5, water_network, adjacency_matrix, visited);
    free(visited);
}