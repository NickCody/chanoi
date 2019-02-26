#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

struct StackItem
{
    int value;
    struct StackItem *next;
};

struct Stack
{
    struct StackItem *top;
};

struct Stack *allocate_stack();
void free_stack(struct Stack *);

void push_stack(struct Stack *s, int v);
int pop_stack(struct Stack *stack);
bool is_empty_stack(struct Stack *stack);
void print_stack(struct Stack *stack);

#endif