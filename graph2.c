//
// Created by itamarq on 30/12/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

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

void delete_all_edges_to_node(pnode *graph_head, int node_id){
    pnode current_node = *graph_head;
    while (current_node != NULL) {

        pedge current_edge = current_node->edges, prev;
        if (current_edge != NULL && current_edge->dest == node_id) {
            current_edge = current_edge->next;
            free(current_edge);
            return;
        }
        while (current_edge != NULL && current_edge->dest != node_id) {
            prev = current_edge;
            current_edge = current_edge->next;
        }
        if (current_edge == NULL) {
            return;
        }
        prev->next = current_edge->next;
        free(current_edge);
    }
}

void delete_all_out_edges(pedge edges_head){
    pedge current_edge = edges_head;
    pedge next;
    while (current_edge != NULL){
        next = current_edge->next;
        free(current_edge);
        current_edge = next;
    }
    edges_head = NULL;
}

void delete_node_from_graph(node **graph_head, int node_id){
    pnode current_node = *graph_head, prev;
    if(current_node != NULL && current_node->id == node_id){
        *graph_head = current_node->next;
        free(current_node);
        return;
    }
    while (current_node != NULL && current_node->id != node_id){
        prev = current_node;
        current_node = current_node->next;
    }
    if(current_node == NULL){
        return;
    }
    delete_all_out_edges(current_node->edges);
    prev->next = current_node->next;
    free(current_node);
}

void add_node_to_graph(node **graph_head, int node_id){
    pnode new_node = (pnode) malloc(sizeof (node));
    if(new_node == NULL){
        return;
    }
    new_node->id = node_id;
    new_node->next = NULL;
    new_node->next = *graph_head;
    *graph_head = new_node;
}

void add_edge_to_node(pnode *graph_head , int src, int dest, int weight){
    pedge edges_head;
    pnode current_node = *graph_head;
    if(current_node != NULL && current_node->id == src){
        edges_head = current_node->edges;
    }
    while (current_node != NULL && current_node->id != src){
        current_node = current_node->next;
    }
    if(current_node == NULL){
        return;
    }
    edges_head = current_node->edges;

    pedge new_edge = (pedge) malloc(sizeof (edge));
    if(new_edge == NULL){
        return;
    }
    new_edge->dest = dest;
    new_edge->weight = weight;
    new_edge->next = edges_head;
    edges_head = new_edge;
}



void init_graph(node **graph_head){
    pnode current_node = *graph_head, next_node;
    while (current_node != NULL){
        next_node = current_node->next;
        delete_all_out_edges(current_node->edges);
        free(current_node);
        current_node = next_node;
    }
    graph_head = NULL;
}

int** build_graph_matrix(pnode *head){
    int count = 0;
    pnode current = *head;
    while (current!=NULL){
        count++;
        current = current->next;
    }
    int **mat = (int**) malloc(count * sizeof (int*));
    for (int i = 0; i <count ; ++i) {
        mat[i] = (int*) malloc(count * sizeof (int));
    }
    return mat;
}
int minDistance(int dist[], bool sptSet[], int count)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < count; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int **mat, int src, int count){
    int dist[count];

    bool sptSet[count];

    for (int i = 0; i < count; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int num = 0; num < count - 1; num++) {
        int u = minDistance(dist, sptSet, count);
        sptSet[u] = true;

        for (int v = 0; v < count; v++)
            if (!sptSet[v] && mat[u][v] && dist[u] != INT_MAX
                && dist[u] + mat[u][v] < dist[v])
                dist[v] = dist[u] + mat[u][v];
    }


}

int shortest_path(pnode *head, int src, int dest){
    int **graph_mat = build_graph_matrix(head);
    int dist;
    int count = 0;
    pnode current = *head;
    while (current!=NULL){
        count++;
        current = current->next;
    }
    dijkstra(graph_mat, src, count);
    dist = graph_mat[src][dest];
    for (int i = 0; i <count ; ++i) {
        free(graph_mat[i]);
    }
    free(graph_mat);
    return dist;
}

int tsp(pnode *head, int* nodes_to_visit){
    int min_dist = INT_MAX;
    int count = 0;
    pnode current = *head;
    while (current!=NULL){
        count++;
        current = current->next;
    }
    for (int i = 0; i <count ; ++i) {
        int current_dist = 0;
        for (int j = 0; j <count ; ++j) {
            if(i == j){
                continue;
            }
            int dist_to_add = shortest_path(head, nodes_to_visit[i], nodes_to_visit[j]);
            current_dist += dist_to_add;
        }
        if(current_dist < min_dist){
            min_dist = current_dist;
        }
    }
    return min_dist;
}
