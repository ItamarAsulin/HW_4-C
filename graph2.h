//
// Created by itamarq on 30/12/2021.
//

#ifndef EX4_GRAPH2_H
#define EX4_GRAPH2_H

typedef struct edge_ {
    int weight;
    int dest;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int id;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void delete_all_edges_to_node(pnode *graph_head, int node_id);
void delete_node_from_graph(node **graph_head, int node_id);
void add_node_to_graph(node **graph_head, int node_id);
void add_edge_to_node(pnode *graph_head , int src, int dest, int weight);
void delete_all_out_edges(pedge edges_head);
void init_graph(node **graph_head);
int shortest_path(pnode *head, int src, int dest);
int tsp(pnode *head, int* nodes_to_visit);
#endif //EX4_GRAPH2_H
