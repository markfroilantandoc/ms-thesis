#include "fluidDynamicsUtil.h"

static double computeFlowLink(int index1, int index2, network *water_network, int **adjacency_matrix, int *visited)
{
    int i, index;
    for (i=0; i<water_network->pipe_count; i++) {
        if ((water_network->links[i].n1 == index1 && water_network->links[i].n2 == index2) ||
            (water_network->links[i].n2 == index1 && water_network->links[i].n1 == index2)) {
            index = i;
            break;
        }
    }

    visited[index] = 1;
    for (i=0; i<water_network->pipe_count; i++) {
        if (water_network->links[i].n1 == index2 && !visited[i]) {
            water_network->links[index].flow += abs(computeFlowLink(index2, water_network->links[i].n2, water_network, adjacency_matrix, visited));
        } else if (water_network->links[i].n2 == index2 && !visited[i]) {
            water_network->links[index].flow += abs(computeFlowLink(index2, water_network->links[i].n1, water_network, adjacency_matrix, visited));
        }
    }
    //water_network->links[index].flow -= water_network->junctions[index1].flow;
    water_network->links[index].flow += water_network->junctions[index2].flow;
    if (index2 < index1)
    {
        water_network->links[index].flow *= -1;
    }
    return water_network->links[index].flow;
}

void computeFlow(network *water_network, int **adjacency_matrix)
{
    int i;
    int *visited = NULL;
    visited = (int *)malloc(water_network->pipe_count * sizeof(int));
    for (i=0; i<water_network->pipe_count; i++) {
        visited[i] = 0;
    }
    for (i=0; i<water_network->pipe_count; i++) {
        if (water_network->links[i].n1 == 0) {
            computeFlowLink(0, water_network->links[i].n2, water_network, adjacency_matrix, visited);
            break;
        }
    }
    free(visited);
}