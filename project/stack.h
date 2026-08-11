#ifndef STACK_H
#define STACK_H

#include "maze.h"//needed for the position struct definition

#define MAX_STACK_SIZE 1000

typedef struct {
    Position items[MAX_STACK_SIZE];
    int top;
} Stack;

void stact_init(Stack *stack);
int stack_push(Stack *stack, Position value);
int stack_pop(Stack *stack, Position *value);
int stack_is_empty(const Stack *stack);
#endif