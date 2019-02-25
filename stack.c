#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct Stack *allocate_stack()
{
    struct Stack *stack = malloc(sizeof(struct Stack));
    stack->top = NULL;

    return stack;
}

void free_stack(struct Stack *stack)
{
    if (stack == NULL)
        return;

    if (stack->top == NULL)
        return;

    while (stack->top)
    {
        pop_stack(stack);
    }

    free(stack);
}

int pop_stack(struct Stack *stack)
{
    if (stack == NULL)
    {
        printf("Popping null stack. Aborting!");
        exit(1);
    }

    if (stack->top == NULL)
    {
        printf("Popping empty stack. Aborting!");
        exit(1);
    }

    struct StackItem *top = stack->top;
    int v = top->value;
    stack->top = top->next;
    free(top);

    return v;
}
void push_stack(struct Stack *stack, int v)
{
    if (stack == NULL)
    {
        printf("Stack is NULL. Aborting!");
        exit(1);
    }

    struct StackItem *newItem = (struct StackItem *)malloc(sizeof(struct StackItem));
    newItem->next = stack->top;
    newItem->value = v;
    stack->top = newItem;
}

int is_empty_stack(struct Stack *stack)
{
    if (stack == NULL)
    {
        printf("Stack is NULL. Aborting!");
        exit(1);
    }

    if (stack->top == NULL)
        return 1;

    return 0;
}

void print_stack(struct Stack *stack)
{
    if (stack == NULL)
    {
        printf("Stack is NULL. Aborting!");
        exit(1);
    }

    struct StackItem *item = stack->top;
    while (item != NULL)
    {
        printf("%d", item->value);

        if (item->next != NULL)
            printf(", ");
        item = item->next;
    }

    printf("\n");
}
