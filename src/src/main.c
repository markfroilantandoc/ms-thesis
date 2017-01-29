#include "main.h"

int main (int argc, char* argv[]) {

    FILE *fp;
    int i;
    float tempx, tempy;
    int num_nodes;

    if (argc < 2) {
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 1;
    }

    ENopen ("", "", "");

    // Scan terminals
    fscanf(fp, "%d\n", &num_nodes);
    for (i=0; i<num_nodes; i++) {
        fscanf(fp, "%f %f\n", &tempx, &tempy);
    }

    // Compute Steiner tree
    if(gst_open_geosteiner() != 0){
		printf("Could not open GeoSteiner\n");
		exit(1);
	}
    gst_close_geosteiner();

    // Compute feasibility of network

    // Display output

    ENclose();
    fclose(fp);

    return 0;

}
