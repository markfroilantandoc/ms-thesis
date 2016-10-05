#include "geosteiner/geosteiner.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Allocate required arrays */
void init(int num_terminals, 
			double **terminals, double **steiner_points, int **edges){
	
	*terminals		= (double *) malloc (sizeof(double) * num_terminals * 2);
	*steiner_points	= (double *) malloc (sizeof(double) * num_terminals * 2);
	*edges			= (int *) malloc (sizeof(int) * num_terminals * 4);
	
}

/* Deallocate arrays used */
void freeArrays(double **terminals, double **steiner_points, int **edges){

	free(*terminals);
	free(*steiner_points);
	free(*edges);

}

/* Generate Random terminals */
void randomize_terminals(int seed, int num_terminals, double *terminals){
	int i;
	
	srand48(1);
	for(i=0; i<num_terminals*2; i++){
		terminals[i] = floor(drand48() * 10000);
	}
	// Debugging: Print generated points
	/*
	for(i=0; i<num_terminals; i++){
		printf("%4d (%9.4f, %9.4f)\n", i, terminals[2*i], terminals[2*i+1]);
	}
	*/
	
}

double getDistance(double x1, double y1, double x2, double y2){
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

/* Output in the form of EPANET input */
void print_graph(int num_terminals, double *terminals, 
					int num_steiner_points, double *steiner_points,
					int num_edges, int *edges){
	int i;
	
	printf("\n[JUNCTIONS]\n");
	printf(";ID\tElevation\tDemand\t\tCoordinates\n");
	for(i=0; i<num_terminals; i++){
		printf("%d\t%d\t\t%d\t;\t(%11f, %11f)\n", i+1, 100, 100,
										terminals[2*i], terminals[2*i+1]);
	}
	for(i=0; i<num_steiner_points; i++){
		printf("%d\t%d\t\t%d\t;\t(%11f, %11f)\n", i+1+num_terminals, 100, 100,
									steiner_points[2*i], steiner_points[2*i+1]);
	}
	
	printf("\n[PIPES]\n");
	printf(";ID\t\tNode1\t\tNode2\t\tLength\t\tDiameter\t\tRoughness\n");
	for(i=0; i<num_edges; i++){
		printf("%d\t\t%d\t\t%d\t\t%f\t\t%d\t\t%d\n", i+1, i, edges[i],
											10.0, 100, 100);
	}
	
	printf("\n[END]\n");
	
}

int main(int argc, char *argv[]){

	int num_terminals, num_steiner_points, num_edges;
	int *edges;
	double steiner_tree_length;
	double *terminals, *steiner_points;

	if(argc < 2){
		num_terminals = 10;
	}else{
		num_terminals = atoi(argv[1]);
	}
	
	init(num_terminals, &terminals, &steiner_points, &edges);
	randomize_terminals(1, num_terminals, terminals);
	
	if(gst_open_geosteiner() != 0){
		printf("Could not open GeoSteiner\n");
		exit(1);
	}
	gst_esmt(num_terminals, terminals, &steiner_tree_length, 
				&num_steiner_points, steiner_points, 
				&num_edges, edges, NULL, NULL);
	gst_close_geosteiner();
	
	print_graph(num_terminals, terminals,
				num_steiner_points, steiner_points,
				num_edges, edges);
	freeArrays(&terminals, &steiner_points, &edges);

	return 0;
	
}
