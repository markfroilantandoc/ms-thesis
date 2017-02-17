#include "main.h"

int main (int argc, char* argv[]) {

    FILE *fp = NULL;
    int i=0, j=0;

    int num_terminals=0, node_count=0, pipe_count=0;
    node *terminals = NULL, *network_nodes = NULL;
    pipe *network_pipes = NULL;
    int **adjacency_matrix = NULL;

    if (argc < 2) {
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 1;
    }

    // Scan terminals from input
    fscanf(fp, "%d\n", &num_terminals);
    terminals = (node *)malloc(num_terminals * sizeof(node));
    for (i=0; i<num_terminals; i++) {
        fscanf(fp, "%lf %lf %lf %lf\n", &(terminals[i].x), &(terminals[i].y), &(terminals[i].elevation), &(terminals[i]).flow);
    }
    fclose(fp);

    // Compute Euclidean Steiner Minimal Tree using Geosteiner
    esmt(num_terminals, terminals, &node_count, &network_nodes, &pipe_count, &network_pipes);
    // Generate adjacency_matrix
    adjacency_matrix = (int **)malloc(node_count * sizeof(int *));
    for (i=0; i<node_count; i++) {
        adjacency_matrix[i] = (int *)malloc(node_count * sizeof(int));
    }
    for (i=0; i<pipe_count; i++) {
        adjacency_matrix[network_pipes[i].n1][network_pipes[i].n2] = 1;
        adjacency_matrix[network_pipes[i].n2][network_pipes[i].n1] = 1;
    }

    // Debug
    printf("Nodes\n");
    for (i=0; i<node_count; i++) {
        printf("%lf %lf\n", network_nodes[i].x, network_nodes[i].y);
    }
    printf("Pipes\n");
    for (i=0; i<pipe_count; i++) {
        printf("%d %d %lf\n", network_pipes[i].n1, network_pipes[i].n2, network_pipes[i].length);
    }

    // Cleanup
    if (adjacency_matrix != NULL) {
        for (i=0; i<node_count; i++) {
            free(adjacency_matrix[i]);
        }
        free(adjacency_matrix);
    }
    if (terminals != NULL) {
        free(terminals);
    }
    if (network_nodes != NULL) {
        free(network_nodes);
    }
    if (network_pipes != NULL) {
        free(network_pipes);
    }

    return 0;

}
