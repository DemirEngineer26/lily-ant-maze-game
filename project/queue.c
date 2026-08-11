#include "queue.h"

void queue_init(Queue *queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

int queue_is_empty(const Queue *queue) {
    return queue->size == 0;
}

int queue_is_full(const Queue *queue) {
    return queue->size == MAX_QUEUE_SIZE;
}
int queue_enqueue(Queue *queue, Position value) {
    if (queue_is_full(queue)) {
        return 0;
    }
    queue->items[queue->rear] = value;
    queue->rear = (queue->rear+1) % MAX_QUEUE_SIZE;
    queue->size++;
    return 1;
}

int queue_dequeue(Queue *queue, Position *value) {
    if (queue_is_empty(queue)) return 0;

    *value = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->size--;
    return 1;
}
