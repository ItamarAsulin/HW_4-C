//
// Created by itamarq on 02/01/2022.
//

#ifndef EX4_QUEUE_H
#define EX4_QUEUE_H

typedef struct Queue_ {
    int front, rear, size;
    unsigned capacity;
    int* array;
}Queue, *pqueue;

struct Queue_* createQueue(unsigned capacity);
int isFull(struct Queue_* queue);
int isEmpty(struct Queue_* queue);
void enqueue(struct Queue_* queue, int item);
int dequeue(struct Queue_* queue);
int front(struct Queue_* queue);
int rear(struct Queue_* queue);
void delete_queue(struct Queue_* queue);
#endif //EX4_QUEUE_H
