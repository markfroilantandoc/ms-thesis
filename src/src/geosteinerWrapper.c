#include "geosteinerWrapper.h"

static void initArrays(int num_terminals, double **terminals, double **steiner_points, int **edges) {

    *terminals = (double *) malloc (sizeof(double) * num_terminals * 2);
    *steiner_points = (double *) malloc (sizeof(double) * num_terminals * 2);
    *edges = (int *) malloc (sizeof(int) * num_terminals * 4);

}

static void freeArrays(double **terminals, double **steiner_points, int **edges) {

    free(*terminals);
    free(*steiner_points);
    free(*edges);

}

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

void esmt(int num_terminals, node *terminals) {

    int _num_terminals, _num_steiner_points, _num_edges;
    int *_edges;
    double _steiner_tree_length;
    double *_terminals, *_steiner_points;

    _num_terminals = num_terminals;
    initArrays(_num_terminals, &_terminals, &_steiner_points, &_edges);
    if(gst_open_geosteiner() != 0){
        printf("Could not open GeoSteiner\n");
        exit(1);
    }
    gst_esmt(_num_terminals, _terminals, &_steiner_tree_length, 
                &_num_steiner_points, _steiner_points, 
                &_num_edges, _edges, NULL, NULL);
    gst_close_geosteiner();
    	print_graph(_num_terminals, _terminals,
				_num_steiner_points, _steiner_points,
				_num_edges, _edges);
    freeArrays(&_terminals, &_steiner_points, &_edges);

}