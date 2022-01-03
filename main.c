#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "graph.h"
#include "node.c"
#include "edge.c"
#include "algo.c"

void empty_graph(pgraph g){
    pnode n = g->nodes;
    while(n != NULL){
        pnode to_delete = n;
        n = n->next;
        delete_node(g, to_delete);
    }
    g->nodes = NULL;
}

int get_number_until_space(char start){
    int x=0;
    char c = start;
    if(start == 0)
        scanf("%c", &c); // Get the first digit
    x = (c -'0');
    scanf("%c", &c); // Get the next digit
    while(c != ' ' && c != '\n'){
        x = (x*10) + (c -'0');
        scanf("%c", &c); // Get the next digit
    }
    return x;
}

int main(){

    char in = ' ';
    graph g;
    g.nodes = NULL;
    pgraph p_g = &g;
    int have_next_cmd = 0;

    while(1){
        if(have_next_cmd == 0){
            scanf("%c", &in);
        }
        // #ifdef DEBUG
        // printf("{input:(%c)}", in);
        // #endif
        have_next_cmd = 0;
        switch (in){
            case 'A':{

                    // Create new Graph
                    scanf("%c", &in); // Get the space
                    int n_size = get_number_until_space(0);
                    #ifdef DEBUG
                    printf("{A cmd {%d}}\n", n_size);
                    #endif

                    if(p_g->nodes != NULL){
                        empty_graph(p_g);
                    }
                }
                break;

            case 'n':{ // Create new node
                    scanf("%c", &in); // Get the space
                    int node_id = get_number_until_space(0);
                    pnode src_node = create_node(p_g, node_id);
                    
                    #ifdef DEBUG
                    printf("{n cmd (%d)}\n",node_id);
                    #endif
                    delete_node_edges(src_node);
                    scanf("%c", &in);
                    while(isdigit(in)){
                        int dst = get_number_until_space(in);
                        pnode dst_node = get_or_create_node(p_g, dst);
                        int w = get_number_until_space(0);
                        add_edge(src_node, dst_node, w);
                        #ifdef DEBUG
                        printf("\t{n: %d -> %d (%d)}\n", node_id, dst, w );
                        #endif
                        scanf("%c", &in); // Get the next input
                    }
                    have_next_cmd = 1;
                }
                break;

            case 'B':{ // Create new node
                    #ifdef DEBUG
                    printf("{B cmd}\n");
                    #endif

                    in='n';
                    have_next_cmd =1;
                }
                break;

            case 'D':{ // Delete node
                    scanf("%c", &in); // Get the space
                    int node_id = get_number_until_space(0);
                    pnode n = get_or_create_node(p_g, node_id);
                    
                    #ifdef DEBUG
                    printf("{D cmd (%d)}\n", node_id);
                    #endif
                    
                    delete_node(p_g, n);
                }
                break;

            case 'S':{ // Shortest path
                    #ifdef DEBUG
                    printf("{S cmd}\n");
                    #endif
                    
                    scanf("%c", &in); // Get the space
                    int node_src = get_number_until_space(0);
                    int node_dst = get_number_until_space(0);

                    pnode n_src = get_or_create_node(p_g, node_src);
                    pnode n_dst = get_or_create_node(p_g, node_dst);
                    shortest_path(p_g, n_src, n_dst);
                }
                break;

            case 'T':{ // TSP
                    #ifdef DEBUG
                    printf("{T cmd}\n");
                    #endif

                    scanf("%c", &in); // Get the space
                    int num = get_number_until_space(0);
                    int* citis = (int*) malloc(sizeof(int)*num);

                    for(int i=0;i<num; i++){
                        citis[i] = get_number_until_space(0);
                    }
                    tsp(p_g, citis, num);
                }
                break;

            case ' ':
                return 0;
                break;

            case '\n':
                return 0;

            case EOF:
                return 0;


            default:
                break;
        }
    }
    return 0;
}