#include "main.h"

int main (int argc, char* argv[]) {

    FILE *fp;
    int i;
    double tempx, tempy;
    int num_terminals;
    node *terminals;

    if (argc < 2) {
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 1;
    }

    // Scan terminals
    fscanf(fp, "%d\n", &num_terminals);
    terminals = (node *)malloc(num_terminals * sizeof(node));

    for (i=0; i<num_terminals; i++) {
        fscanf(fp, "%lf %lf\n", &tempx, &tempy);
        terminals[i].x = tempx;
        terminals[i].y = tempy;
    }

    fclose(fp);

    esmt(num_terminals, terminals);

    // Try Epanet library
    ENopen ("", "", "");
    ENclose();

    return 0;

}
