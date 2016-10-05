#include "geosteiner/geosteiner.h"
#include "epanet/toolkit.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_TERMS 10

int main(int argc, char *argv[]){
	
	int i;
	int num_steiner_points, num_edges;
	int edges[NUM_TERMS*4];
	double steiner_tree_length;
	double terminals[NUM_TERMS*2], steiner_points[(NUM_TERMS)*2];

	if(gst_open_geosteiner() != 0){
		printf("Could not open GeoSteiner\n");
		exit(1);
	}

	// Randomize NUM_TERMS points
	srand48(1);
	for(i=0; i<NUM_TERMS*2; i++){
		terminals[i] = floor(drand48() * 10000);
	}

	// Compute Euclidean Steiner Tree
	gst_esmt(NUM_TERMS, terminals, &steiner_tree_length, &num_steiner_points, steiner_points, &num_edges, edges, NULL, NULL);

	// Print GeoSteiner Output
	printf("Length of Steiner Tree:\n\t%f\n", steiner_tree_length);
	printf("Terminals:\n");
	for(i=0; i<NUM_TERMS; i++){
		printf("\t%d: (%f, %f)\n", i, terminals[2*i], terminals[2*i+1]);
	}
	printf("%d Steiner Points:\n", num_steiner_points);
	for(i=0; i<num_steiner_points; i++){
		printf("\t%d: (%f, %f)\n", i, steiner_points[2*i], steiner_points[2*i+1]);
	}
	printf("%d Edges:\n", num_edges);
	for(i=0; i<num_edges; i++){
		printf("\t%d %d\n", i, edges[i]);
	}
	gst_close_geosteiner();

	return 0;

}
