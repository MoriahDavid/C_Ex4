// #define DEBUG // Use for debug mode


#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    unsigned int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int weight;
    int visited;    
} node, *pnode;

typedef struct G_{
    pnode nodes;
    int size;
} graph, *pgraph;


pnode get_or_create_node(pgraph graph, int id);
pnode get_node(pgraph graph, int id);
void delete_node_edges(pnode n);
void add_edge(pnode n, pnode dest, int w);

void shortest_path(pgraph graph, pnode n_src, pnode n_dst);
void tsp(pgraph graph, int citis[], int num);

#endif
