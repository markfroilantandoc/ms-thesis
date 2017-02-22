#include "main.h"

int main (int argc, char* argv[]) {

    FILE *fp = NULL;
    int i=0, j=0;

    int num_terminals=0;
    node *terminals = NULL;
    network water_network;
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
    esmt(num_terminals, terminals, &water_network);
    // Generate adjacency_matrix
    adjacency_matrix = (int **)malloc(water_network.node_count * sizeof(int *));
    for (i=0; i<water_network.node_count; i++) {
        adjacency_matrix[i] = (int *)malloc(water_network.node_count * sizeof(int));
    }
    for (i=0; i<water_network.pipe_count; i++) {
        adjacency_matrix[water_network.links[i].n1][water_network.links[i].n2] = 1;
        adjacency_matrix[water_network.links[i].n2][water_network.links[i].n1] = 1;
    }
    // Compute pipe flows
    computeFlow(&water_network, adjacency_matrix);

    // Debug
    printf("Nodes\n");
    for (i=0; i<water_network.node_count; i++) {
        printf("%lf %lf\n", water_network.junctions[i].x, water_network.junctions[i].y);
    }
    printf("Pipes\n");
    for (i=0; i<water_network.pipe_count; i++) {
        printf("%d %d %lf %lf\n", water_network.links[i].n1, water_network.links[i].n2, water_network.links[i].length, water_network.links[i].flow);
    }

    // Cleanup
    if (adjacency_matrix != NULL) {
        for (i=0; i<water_network.node_count; i++) {
            free(adjacency_matrix[i]);
        }
        free(adjacency_matrix);
    }
    if (terminals != NULL) {
        free(terminals);
    }
    if (water_network.junctions != NULL) {
        free(water_network.junctions);
    }
    if (water_network.links != NULL) {
        free(water_network.links);
    }

    return 0;

}
