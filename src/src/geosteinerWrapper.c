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

double esmt(int num_terminals, node *terminals, network *water_network) {

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
    water_network->node_count = _num_terminals + _num_steiner_points;
    water_network->junctions = (node *)malloc((_num_terminals + _num_steiner_points) * sizeof(node));
    j=0;
    for (i=0; i<_num_terminals; i++) {
        (water_network->junctions)[j].x = _terminals[2*i];
        (water_network->junctions)[j].y = _terminals[2*i+1];
        (water_network->junctions)[j].elevation = terminals[i].elevation;
        (water_network->junctions)[j].flow = terminals[i].flow;
        j++;
    }
    for (i=0; i<_num_steiner_points; i++) {
        (water_network->junctions)[j].x = _steiner_points[2*i];
        (water_network->junctions)[j].y = _steiner_points[2*i+1];
        (water_network->junctions)[j].elevation = _default_elevation;
        (water_network->junctions)[j].flow = _default_flow;
        j++;
    }
    water_network->pipe_count = _num_edges;
    water_network->links = (pipe *)malloc(_num_edges * sizeof(pipe));
    for (i=0; i<_num_edges; i++) {
        (water_network->links)[i].n1 = _edges[2*i];
        (water_network->links)[i].n2 = _edges[2*i+1];
        (water_network->links)[i].length = getDistance((water_network->junctions)[_edges[2*i]], (water_network->junctions)[_edges[2*i+1]]);
        (water_network->links)[i].diameter = _default_diameter;
        (water_network->links)[j].flow = _default_flow;
    }
    
    // Cleanup
    freeArrays(&_terminals, &_steiner_points, &_edges);

    // Return size of network
    return _steiner_tree_length;

}