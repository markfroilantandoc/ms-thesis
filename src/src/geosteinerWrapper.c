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

int esmt(int num_terminals, node *terminals, node **network) {

    int _num_terminals, _num_steiner_points, _num_edges;
    int *_edges;
    double _steiner_tree_length;
    double *_terminals, *_steiner_points;
	int i, j;

	// Initializations
    _num_terminals = num_terminals;
    initArrays(_num_terminals, &_terminals, &_steiner_points, &_edges);
	for (i=0; i<_num_terminals; i++) {
		_terminals[2*i] = terminals[i].x;
		_terminals[2*i+1] = terminals[i].y;
	}

	// Compute euclidean steiner minimal tree
    if(gst_open_geosteiner() != 0){
        printf("Could not open GeoSteiner\n");
        exit(1);
    }
    gst_esmt(_num_terminals, _terminals, &_steiner_tree_length, 
                &_num_steiner_points, _steiner_points, 
                &_num_edges, _edges, NULL, NULL);
    gst_close_geosteiner();

	// Copy to output variables
	*network = (node *)malloc((_num_terminals + _num_steiner_points) * sizeof(node));
	j=0;
	for (i=0; i<_num_terminals; i++) {
		(*network)[j].x = _terminals[2*i];
		(*network)[j].y = _terminals[2*i+1];
		j++;
	}
	for (i=0; i<_num_steiner_points; i++) {
		(*network)[j].x = _steiner_points[2*i];
		(*network)[j].y = _steiner_points[2*i+1];
		j++;
	}
	
	// Cleanup
    freeArrays(&_terminals, &_steiner_points, &_edges);

	// Return size of network
	return _num_terminals + _num_steiner_points;

}