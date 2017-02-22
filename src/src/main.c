#include "main.h"

int main (int argc, char* argv[]) {

    FILE *fp = NULL;
    int i=0, j=0;

    int num_terminals=0;
    node *terminals = NULL;
    network waterNetwork;
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
    esmt(num_terminals, terminals, &waterNetwork);
    // Generate adjacency_matrix
    adjacency_matrix = (int **)malloc(waterNetwork.node_count * sizeof(int *));
    for (i=0; i<waterNetwork.node_count; i++) {
        adjacency_matrix[i] = (int *)malloc(waterNetwork.node_count * sizeof(int));
    }
    for (i=0; i<waterNetwork.pipe_count; i++) {
        adjacency_matrix[waterNetwork.links[i].n1][waterNetwork.links[i].n2] = 1;
        adjacency_matrix[waterNetwork.links[i].n2][waterNetwork.links[i].n1] = 1;
    }
    // Compute pipe flows
    computeFlow(&waterNetwork, adjacency_matrix);

    // Debug
    printf("Nodes\n");
    for (i=0; i<waterNetwork.node_count; i++) {
        printf("%lf %lf\n", waterNetwork.junctions[i].x, waterNetwork.junctions[i].y);
    }
    printf("Pipes\n");
    for (i=0; i<waterNetwork.pipe_count; i++) {
        printf("%d %d %lf\n", waterNetwork.links[i].n1, waterNetwork.links[i].n2, waterNetwork.links[i].length);
    }

    // Cleanup
    if (adjacency_matrix != NULL) {
        for (i=0; i<waterNetwork.node_count; i++) {
            free(adjacency_matrix[i]);
        }
        free(adjacency_matrix);
    }
    if (terminals != NULL) {
        free(terminals);
    }
    if (waterNetwork.junctions != NULL) {
        free(waterNetwork.junctions);
    }
    if (waterNetwork.links != NULL) {
        free(waterNetwork.links);
    }

    return 0;

}
