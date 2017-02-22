#ifndef _types_
#define _types_
typedef struct {
    double x;
    double y;
    double elevation;
    double flow;
} node;

typedef struct {
    int n1;
    int n2;
    double length;
    double diameter;
    double flow;
} pipe;

typedef struct {
    int node_count;
    node *junctions;
    int pipe_count;
    pipe *links;
} network;
#endif
