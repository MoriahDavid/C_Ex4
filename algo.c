#include <stdio.h>
#include "graph.h"

void shortest_path(pgraph graph, pnode n_src, pnode n_dst){
    #ifdef DEBUG
    printf("\t{Shortest path %d -> %d}\n", n_src->node_num, n_dst->node_num);
    #endif



}

void tsp(pgraph graph, int citis[], int num){
    #ifdef DEBUG
    printf("\t{TSP %d", citis[0]);
    for(int i=1; i<num;i++) printf(" -> %d", citis[i]);
    printf("}\n");
    #endif

    

}