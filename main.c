#include <stdio.h>
#include <stdlib.h>
#include "graph2.h"

typedef struct GRAPH_ {
    pnode graph_head;
    int num_of_nodes;
} graph, *pgraph;

int main() {
    int flag_for_main = 1;
    pgraph main_graph = (pgraph) malloc(sizeof(graph));
    while (flag_for_main) {
        char input;
        scanf("%c", &input);
        if (input == 'A') {
            int num_of_nodes;
            scanf("%d", &num_of_nodes);
            init_graph(&main_graph->graph_head);
            main_graph->num_of_nodes = num_of_nodes;
            int flag = 1;
            char new_node_n;
            scanf("%c", &new_node_n);
            while (flag) {
                if (new_node_n == 'n') {
                    int node_id;
                    int dest;
                    int weight;
                    scanf("%d", &node_id);
                    add_node_to_graph(&main_graph->graph_head, node_id);
                    while (scanf("%d %d", &dest, &weight)) {
                        add_edge_to_node(&main_graph->graph_head, node_id, dest, weight);
                    }
                }
                scanf("%c", &new_node_n);
                if (new_node_n == 'n') {
                    continue;
                } else {
                    flag = 0;
                }
            }
        }

        if(input == 'B'){
            int node_id;
            int dest;
            int weight;
            scanf("%d", &node_id);
                delete_node_from_graph(&main_graph->graph_head, node_id);
                add_node_to_graph(&main_graph->graph_head, node_id);
                while (scanf("%d %d", &dest, &weight)){
                    add_edge_to_node(&main_graph->graph_head, node_id, dest, weight);
                }

        }

        if (input == 'D'){
            int node_to_remove;
            scanf("%d", &node_to_remove);
            delete_node_from_graph(&main_graph->graph_head, node_to_remove);
            delete_all_edges_to_node(&main_graph->graph_head, node_to_remove);
        }

        if(input == 'S'){
            int src;
            int dest;
            scanf("%d %d", &src, &dest);
            int result = shortest_path(&main_graph->graph_head, src, dest);
            printf("Dijsktra shortest path: %d", result);
        }

        if(input == 'T'){
            int num_of_nodes;
            int shortest_path_through_all;
            scanf("%d", &num_of_nodes);
            int *nodes_arr = (int*) malloc(num_of_nodes * sizeof (int));
            shortest_path_through_all = tsp(&main_graph->graph_head, nodes_arr);
            printf("TSP shortest path: %d", shortest_path_through_all);
        }

        if(input == EOF || input == '\n') {
            flag_for_main = 0;
        }
    }
    return 1;
}
