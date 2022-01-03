//
// Created by itamarq on 30/12/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "queue.h"
#include "stack.h"

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

void print_graph(pnode *graph_head);

pnode get_node(pnode *graph_head, int node_id) {
    pnode current_node;
    current_node = *graph_head;
    if (current_node != NULL && current_node->id == node_id) {
        return current_node;
    }
    while (current_node != NULL && current_node->id != node_id) {
        current_node = current_node->next;
    }
    if (current_node == NULL) {
        return NULL;
    }
    return current_node;

}

void delete_all_out_edges(pnode *graph_head, int node_id) {
    pnode current_node = get_node(graph_head, node_id);
    pedge current_edge = current_node->edges;
    pedge temp;
    while (current_edge != NULL) {
        temp = current_edge->next;
        current_edge->next = NULL;
        free(current_edge);
        current_edge = temp;
    }
    free(current_edge);
}

void remove_dest_node_from_edges(pnode edges_head, int node_id) {
    pedge temp = edges_head->edges, prev;
    if (temp != NULL && temp->dest == node_id) {
        edges_head->edges = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->dest != node_id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void delete_all_in_edges(pnode *graph_head, int node_id) {
    pnode current_node = *graph_head;
    if (current_node->id == node_id) {
        current_node = current_node->next;
    }
    while (current_node != NULL && current_node->id != node_id) {
        remove_dest_node_from_edges(current_node, node_id);
        current_node = current_node->next;
    }
}


void delete_node_from_graph_without_in_edges(node **graph_head, int node_id) {
    pnode current_node = *graph_head, prev;
    if (current_node != NULL && current_node->id == node_id) {
        delete_all_out_edges(graph_head, node_id);
        graph_head = &current_node->next;
        free(current_node);
        return;
    }
    while (current_node != NULL && current_node->id != node_id) {
        prev = current_node;
        current_node = current_node->next;
    }
    if (current_node == NULL) {
        return;
    }
    delete_all_out_edges(graph_head, node_id);
    prev->next = current_node->next;
    free(current_node);
}

void delete_node_from_graph_with_in_edges(pnode *graph_head, int node_id) {
    pnode current_node = *graph_head, prev;
    if (current_node != NULL && current_node->id == node_id) {
        delete_all_in_edges(graph_head, node_id);
        delete_all_out_edges(graph_head, node_id);
        *graph_head = current_node->next;
        free(current_node);
        return;
    }
    while (current_node != NULL && current_node->id != node_id) {
        prev = current_node;
        current_node = current_node->next;
    }
    if (current_node == NULL) {
        return;
    }
    delete_all_out_edges(graph_head, node_id);
    delete_all_in_edges(graph_head, node_id);
    prev->next = current_node->next;
    free(current_node);
}

void add_node_to_graph(pnode *graph_head, int node_id) {
    pnode new_node = (pnode) malloc(sizeof(node));
    if (new_node == NULL) {
        return;
    }
    new_node->id = node_id;
    new_node->edges = NULL;
    new_node->next = *graph_head;
    *graph_head = new_node;
}

void add_edge_to_node(pnode *graph_head, int src, int dest, int weight) {
    pedge edges_head;
    pedge new_edge = (pedge) malloc(sizeof(edge));
    if (new_edge == NULL) {
        return;
    }
    pnode current_node = get_node(graph_head, src);
    edges_head = current_node->edges;
    new_edge->dest = dest;
    new_edge->weight = weight;
    new_edge->next = edges_head;
    current_node->edges = new_edge;
}


void init_graph(pnode *graph_head) {
    pnode current_node = *graph_head, next_node;
    while (current_node != NULL) {
        next_node = current_node->next;
        delete_all_out_edges(graph_head, current_node->id);
        free(current_node);
        current_node = next_node;
    }
    graph_head = NULL;
}

int dijkstra(int src, int dest, int count, pnode *graph_head) {
    int total_weight;
    int current_node_id;
    pedge current_node_edge;
    pnode current_node;
    int current_dest_id;
    int weight;
    int current_weight;
    int shortest_path_weight;

    int map_dist[2000];
    for (int i = 0; i <150 ; ++i) map_dist[i] = INT_MAX;

    pqueue neighbors = createQueue(2500);
    map_dist[src] = 0;
    enqueue(neighbors, src);
    while (!isEmpty(neighbors)) {
        current_node_id = dequeue(neighbors);
        current_node = get_node(graph_head, current_node_id);
        current_node_edge = current_node->edges;
        while (current_node_edge != NULL) {
            current_dest_id = current_node_edge->dest;
            weight = current_node_edge->weight;
            total_weight = map_dist[current_node_id] + weight;
            current_weight = map_dist[current_dest_id];
            if ( total_weight < current_weight) {
                map_dist[current_dest_id] = total_weight;
                enqueue(neighbors, current_dest_id);
            }
            current_node_edge = current_node_edge->next;
        }
    }
    delete_queue(neighbors);
    shortest_path_weight = map_dist[dest];
    if(shortest_path_weight == INT_MAX){
        return -1;
    }
    return shortest_path_weight;
}

int shortest_path(pnode *head, int src, int dest) {
    int dist;
    int count = 0;
    pnode current = *head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    dist = dijkstra(src, dest, count, head);
    return dist;
}

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(int *a, int current_depth, int max_depth, pqueue results, pnode *graph_head, int count) {
    int current_dist;
    if (current_depth == max_depth) {
        int current_result = 0;
        for (int i = 0; i < max_depth; ++i) {
            int curr_src = a[i];
            int curr_dest = a[i+1];
            current_dist = dijkstra(curr_src, curr_dest, count, graph_head);
            if (current_dist == -1) {
                current_result = INT_MAX;
                enqueue(results, current_result);
                return;
            } else {
                current_result += current_dist;
            }
        }
        enqueue(results, current_result);
    } else {
        for (int i = current_depth; i <= max_depth; i++) {
            swap((a + current_depth), (a + i));
            permute(a, current_depth + 1, max_depth, results, graph_head, count);
            swap((a + current_depth), (a + i)); //backtrack
        }
    }
}

int tsp(pnode *graph_head, int *nodes_to_visit, int size) {
    int min_dist = INT_MAX;
    int curr_dist = 0;
    int num_of_permuts = 1;
    int count = 0;
    pnode current_node = *graph_head;
    for (int i = size; i > 0; --i) {
        num_of_permuts *= i;
    }
    pqueue results = createQueue(num_of_permuts);
    while (current_node != NULL){
        count++;
        current_node = current_node->next;
    }
    permute(nodes_to_visit, 0, size - 1, results, graph_head, count);
    while (!isEmpty(results)) {
        curr_dist = dequeue(results);
        if (curr_dist < min_dist && curr_dist >= 0) {
            min_dist = curr_dist;
        }
    }
    delete_queue(results);
    return min_dist;
}

void print_graph(pnode *graph_head) {
    if (*graph_head == NULL) {
        return;
    }
    pedge current_edges = NULL;
    pnode current_node = NULL;
    printf("\n");
    current_node = *graph_head;
    current_node->id = (*graph_head)->id;
    while (current_node != NULL) {

        printf("%d", current_node->id);
        current_edges = current_node->edges;
        if (current_edges == NULL) {
            printf("\n");
            current_node = current_node->next;
            continue;
        }
        while (current_edges != NULL) {
            printf(" ---%d---> %d", current_edges->weight, current_edges->dest);
            current_edges = current_edges->next;
        }
        printf("\n");
        current_node = current_node->next;
    }
    printf("\n");
}

void delete_graph(pnode *graph_head) {
    pnode current = *graph_head, temp;
    while (current != NULL) {
        delete_all_out_edges(&current, current->id);
        temp = current->next;
        free(current);
        current = temp;
    }
    free(temp);
    graph_head = NULL;
}

