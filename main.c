#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

typedef struct GRAPH_ {
    pnode graph_head;
} graph, *pgraph;


int main() {
    char input;
    int num_of_nodes_graph;
    int num_of_nodes_to_travel;
    int flag_for_A;
    int node_id;
    int dest;
    int weight;
    int src;
    int shortest_path_through_all;

    int flag_first_row = 1;
    int flag_for_main = 1;
    pgraph main_graph = (pgraph) malloc(sizeof(graph));
    pnode graph_head = NULL;
    main_graph->graph_head = graph_head;


    while (flag_for_main) {

        scanf("%c", &input);

        if (input == ' ') {
            continue;
        }

        if (input == 'A') {
            if (main_graph->graph_head != NULL) {
                delete_graph(&main_graph->graph_head);
                main_graph->graph_head = NULL;
            }
            scanf("%d", &num_of_nodes_graph);
            init_graph(&main_graph->graph_head);
            flag_for_A = 1;
            char new_node_n;
            scanf(" %c", &new_node_n);
            while (flag_for_A) {
                if (new_node_n == 'n') {
                    int node_id;
                    int dest;
                    int weight;
                    scanf(" %d", &node_id);
                    add_node_to_graph(&main_graph->graph_head, node_id);
                    while (scanf(" %d %d", &dest, &weight)) {
                        add_edge_to_node(&main_graph->graph_head, node_id, dest, weight);
                    }
                }
                scanf(" %c", &new_node_n);
                if (new_node_n == 'n') {
                    continue;
                } else {
                    input = new_node_n;
                    flag_for_A = 0;
                }
            }
        }

        if (input == 'B') {
            scanf(" %d", &node_id);
            delete_node_from_graph_without_in_edges(&main_graph->graph_head, node_id);
            add_node_to_graph(&main_graph->graph_head, node_id);
            while (scanf(" %d %d", &dest, &weight)) {
                add_edge_to_node(&main_graph->graph_head, node_id, dest, weight);
            }
        }

        if (input == 'D') {
            int node_to_remove;
            scanf("%d", &node_to_remove);
            delete_node_from_graph_with_in_edges(&main_graph->graph_head, node_to_remove);
        }

        if (input == 'S') {
            scanf(" %d %d", &src, &dest);
            int result = shortest_path(&main_graph->graph_head, src, dest);
            printf("Dijsktra shortest path: %d \n", result);


        }

        if (input == 'T') {

            scanf(" %d", &num_of_nodes_to_travel);
            int *nodes_arr = (int *) malloc(num_of_nodes_to_travel * sizeof(int));
            for (int i = 0; i < num_of_nodes_to_travel; ++i) {
                int num_to_put;
                scanf(" %d", &num_to_put);
                nodes_arr[i] = num_to_put;
            }
            int dist = tsp(&main_graph->graph_head, nodes_arr, num_of_nodes_to_travel);
            shortest_path_through_all = dist;
            if (shortest_path_through_all == INT_MAX) {
                shortest_path_through_all = -1;
            }

            printf("TSP shortest path: %d \n", shortest_path_through_all);
            free(nodes_arr);

        }

        if (input == EOF || input == '\n') {
            delete_graph(&main_graph->graph_head);
            free(main_graph);
            flag_for_main = 0;
        }
    }
    return 0;
}
