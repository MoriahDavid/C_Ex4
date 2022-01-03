#include <stdlib.h>
#include "graph.h"

void add_edge(pnode n, pnode dest, int w){
    pedge last = n->edges;
    pedge new = (pedge) malloc(sizeof(edge));
    new->weight = w;
    new->endpoint = dest;
    new->next = last;
    n->edges = new;
}