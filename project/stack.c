#include "stack.h"

void stack_init(Stack *stack) {
    //TODO. initialize with stack being the pointer and top being the struct
    //top being set to -1 means there are no variables yet
    stack->top = -1;
}
int stack_push(Stack *stack, Position value) {
    //TODO lily moves to a new tile so write the location onto a new place and stack it on top 
    if (stack->top >= MAX_STACK_SIZE - 1) {
        return 0;
    }
    stack->items[++(stack->top)] = value;
    return 1;

}
int stack_pop(Stack *stack, Position *value) {
    //TODO if lily hits a dead end, she must go back be taking the last step off the pile
    if (stack_is_empty(stack)) {
        return 0;
    }
    *value = stack->items[(stack->top)--];
    return 1;
    
}

int stack_is_empty(const Stack *stack) {
    //TODO check if the top is still -1
    //return 1 if the top is still empty, 0 if not. 
    return stack->top == -1;

}