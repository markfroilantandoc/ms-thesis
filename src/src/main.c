#include "main.h"

int main (int argc, char* argv[]) {

    FILE *fp = NULL;
    int i=0;
    double tempx=0, tempy=0;
    int num_terminals=0, network_size=0;
    node *terminals = NULL, *network = NULL;
    pipe *network_pipes = NULL;

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
        fscanf(fp, "%lf %lf\n", &tempx, &tempy);
        terminals[i].x = tempx;
        terminals[i].y = tempy;
    }
    fclose(fp);

    // Compute Euclidean Steiner Minimal Tree using Geosteiner
    network_size = esmt(num_terminals, terminals, &network);

    // Debug
    for (i=0; i<network_size; i++) {
        printf("%lf %lf\n", network[i].x, network[i].y);
    }

    // Cleanup
    if (terminals != NULL) {
        free(terminals);
    }
    if (network != NULL) {
        free(network);
    }

    return 0;

}
