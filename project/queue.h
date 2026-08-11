
#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"

#define MAX_QUEUE_SIZE 1000

typedef struct {
    Position items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void queue_init(Queue *queue);
int queue_enqueue(Queue *queue, Position value);
int queue_dequeue(Queue *queue, Position *value);
int queue_is_empty(const Queue *queue);

#endif