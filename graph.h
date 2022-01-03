//
// Created by itamarq on 30/12/2021.
//

#ifndef EX4_GRAPH_H
#define EX4_GRAPH_H
#include "queue.h"
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

void delete_node_from_graph_without_in_edges(node **graph_head, int node_id);
void delete_node_from_graph_with_in_edges(pnode *graph_head, int node_id);
void add_node_to_graph(pnode *graph_head, int node_id);
void add_edge_to_node(pnode *graph_head , int src, int dest, int weight);
void init_graph(pnode *graph_head);
int shortest_path(pnode *head, int src, int dest);
int tsp(pnode *graph_head, int* nodes_to_visit, int size);
void print_graph(pnode *graph_head);
void delete_graph(pnode *graph_head);
#endif //EX4_GRAPH_H
