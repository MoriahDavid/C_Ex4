#include <stdlib.h>
#include "graph.h"

pnode get_or_create_node(pgraph graph, int id){
    pnode n = get_node(graph, id);
    if (n!=NULL){
        return n;
    }

    n = (pnode) malloc(sizeof(node));
    #ifdef DEBUG
    printf("\t[create node %d (%p)]\n", id, n);
    #endif
    n->next = graph->nodes;
    n->node_num = id;
    n->edges = NULL;
    graph->nodes = n;
    return n;
}

pnode get_node(pgraph graph, int id){
    pnode n = graph->nodes;
    while(n != NULL){
        if(n->node_num == id){
            return n;
        }
        n = n->next;
    }
    return NULL;
}

void delete_node_edges(pnode n){
    pedge e = n->edges;
    while(e != NULL){
        #ifdef DEBUG
        printf("\t{deleting edge %d -> %d (%d)}\n", n->node_num, e->endpoint->node_num, e->weight);
        #endif
        pedge to_free = e;
        e = e->next;
        free(to_free);
    }
    n->edges = NULL;
}

void delete_node_in_edges(pgraph g, pnode node){
    pnode n = g->nodes;
    while(n != NULL){ // Go over all node
        pedge e = n->edges;
        while(e !=NULL && e->endpoint->node_num == node->node_num){ // if its the first edges on node
            #ifdef DEBUG
            printf("\t{deleting edge %d -> %d (%d)}\n", n->node_num, e->endpoint->node_num, e->weight);
            #endif
            pedge to_free = e;
            n->edges = e->next;
            free(to_free);
            e=n->edges;
        }
        e = n->edges;
        if(e!=NULL){
            while(e->next != NULL){ // for each node check if an edge is going to 'node' and delete it.
                if(e->next->endpoint->node_num == node->node_num){
                    #ifdef DEBUG
                    printf("\t{deleting edge %d -> %d (%d)}\n", n->node_num, e->next->endpoint->node_num, e->next->weight);
                    #endif
                    pedge to_free = e->next;
                    e->next = e->next->next;
                    free(to_free);
                    continue;
                }
                e = e->next;
            }
        }
        n = n->next;
    }
}


pnode create_node(pgraph graph, int id){
    // Check if the node is already exist
    pnode n = get_node(graph, id);
    if(n != NULL){ 
        delete_node_edges(n);
    }
    else{
        n = (pnode) malloc(sizeof(node));
        n->node_num = id;
        n->edges = NULL;
        n->next = graph->nodes;
        graph->nodes = n;
    }
    return n;
}

void delete_node(pgraph graph, pnode node){
    delete_node_edges(node);
    delete_node_in_edges(graph, node);
    pnode n = graph->nodes;
    if(n->node_num == node->node_num){ // 'node' is the graph head
        graph->nodes = node->next;
        free(node);
        return;
    }
    while(n->next != NULL){ // 'node' is in the nodes linked list
        if(n->next->node_num == node->node_num){ // find who point 'node' and change it.
            n->next = node->next;
            free(node);
            return;
        }
        n = n->next;
    }   
}