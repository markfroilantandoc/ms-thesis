#include "main.h"

int main (int argc, char* argv[]) {

    FILE *fp;
    int i;
    float tempx, tempy;
    int num_terminals;

    if (argc < 2) {
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 1;
    }

    // Scan terminals
    fscanf(fp, "%d\n", &num_terminals);
    printf("%d\n", num_terminals);
    for (i=0; i<num_terminals; i++) {
        fscanf(fp, "%f %f\n", &tempx, &tempy);
        printf("%f %f\n", tempx, tempy);
    }

    fclose(fp);

    // Try GeoSteiner library
    if(gst_open_geosteiner() != 0){
		printf("Could not open GeoSteiner\n");
		exit(1);
	}
    gst_close_geosteiner();

    // Try Epanet library
    ENopen ("", "", "");
    ENclose();

    return 0;

}
