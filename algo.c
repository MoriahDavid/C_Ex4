#include <stdio.h>
#include <limits.h>
#include "graph.h"

int min_weight;

/**
 * @brief reset the visited and weight values of the nodes in the given graph.
 * 
 * @param graph 
 */
void reset_nodes(pgraph graph){
    pnode n = graph->nodes;
    while(n != NULL){
        n->weight = INT_MAX;
        n->visited = 0;
        n = n->next;
    }
}

/**
 * @briefGet the node that not visited yet with the min weight.
 * 
 * @param g 
 * @return pnode 
 */
pnode get_node_min_w(pgraph g){
    pnode min_n = NULL;
    int min_w = INT_MAX;
    pnode n = g->nodes;
    while(n != NULL){
        if(n->visited == 0 && n->weight <= min_w){
            min_w = n->weight;
            min_n = n;
        }
        n = n->next;
    }
    return min_n;
}

/**
 * @brief Run the gijkstra algo on the graph.
 * 
 * @param graph 
 * @param src 
 */
void dijkstra(pgraph graph, pnode src){
    reset_nodes(graph);
    int visiteds = 0;
    src->weight = 0;

    while(visiteds < graph->size){
        pnode u = get_node_min_w(graph);
        u->visited = 1;
        visiteds++;
        if(u == NULL) continue;
        pedge e = u->edges;
        while(e != NULL){
            pnode v = e->endpoint;
            #ifdef DEBUG
            printf("%d --(%d)-> %d\n", u->node_num, e->weight ,v->node_num);
            #endif
            if(v->visited == 0){
                if(v->weight > u->weight + e->weight){
                    v->weight = u->weight + e->weight;
                }
            }
            e = e->next;
        }
    }
}

/**
 * @brief Prints the shortest path from src to dest.
 * 
 * @param graph 
 * @param n_src 
 * @param n_dst 
 */
void shortest_path(pgraph graph, pnode n_src, pnode n_dst){
    #ifdef DEBUG
    printf("\t{Shortest path %d -> %d}\n", n_src->node_num, n_dst->node_num);
    #endif

    dijkstra(graph, n_src);
    printf("Dijsktra shortest path: %d \n", n_dst->weight);
}
/**
 * @brief Swap a with b.
 * 
 * @param a 
 * @param b 
 */
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Returns the path weight of the given path array.
 * 
 * @param graph 
 * @param arr 
 * @param size 
 * @return int 
 */
int route_weight(pgraph graph, int arr[], int size){
    int w = 0;
    for(int i=0; i<size-1; i++){
        pnode n1 = get_node(graph, arr[i]);
        pnode n2 = get_node(graph, arr[i+1]);
        dijkstra(graph, n1);
        if(n2->weight == INT_MAX) return INT_MAX;
        w = w + (n2->weight);
    }
    return w;
}

/**
 * @brief Check all possible route weight and save the min weight on the global weight var.
 * 
 * @param g 
 * @param arr 
 * @param start 
 * @param end 
 */
void permutation(pgraph g, int *arr, int start, int end)
{
    if(start == end){
        int w = route_weight(g, arr, end+1);
        if(w < min_weight) min_weight = w;

        return;
    }
    
    for(int i=start;i<=end;i++){
        swap((arr+i), (arr+start));
        permutation(g, arr, start+1, end);
        swap((arr+i), (arr+start));
    }
}

void tsp(pgraph graph, int citis[], int num){
    #ifdef DEBUG
    printf("\t{TSP (%d) %d", num, citis[0]);
    for(int i=1; i<num;i++) printf(" -> %d", citis[i]);
    printf("}\n");
    #endif

    min_weight = INT_MAX;
    permutation(graph, citis, 0, num-1); // Check all possibles routes
    if(min_weight == INT_MAX) min_weight = -1; 
    printf("TSP shortest path: %d \n", min_weight);
}