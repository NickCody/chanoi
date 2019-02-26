#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

#define NUM_TOWERS 3
#define NUM_DISCS 3

void print_towers(struct Stack **towers);
bool is_final_state(struct Stack **towers);
void move_smallest(struct Stack **towers);
void move_non_smallest(struct Stack **towers);

int main(int argc, char **argv)
{

    // allocate
    struct Stack *towers[NUM_TOWERS];
    for (int i = 0; i < NUM_TOWERS; i++)
        towers[i] = allocate_stack();

    // initialize
    for (int i = NUM_DISCS; i > 0; i--)
        push_stack(towers[0], i);

    // Algorithm: A simple solution for the toy puzzle is to alternate
    // moves between the smallest piece and a non-smallest piece. When
    // moving the smallest piece, always move it to the next position
    // in the same direction (to the right if the starting number of
    // pieces is even, to the left if the starting number of pieces is
    // odd). If there is no tower position in the chosen direction, move
    // the piece to the opposite end, but then continue to move in the
    // correct direction. For example, if you started with three pieces,
    // you would move the smallest piece to the opposite end, then
    // continue in the left direction after that. When the turn is to
    // move the non-smallest piece, there is only one legal move.
    // Doing this will complete the puzzle in the fewest moves.
    //  -- Wikipedia

    int steps = 1;
    print_towers(towers);
    move_smallest(towers);

    while (!is_final_state(towers))
    {
        move_non_smallest(towers);
        print_towers(towers);
        move_smallest(towers);
        print_towers(towers);
        steps += 2;
    }

    printf("Finished in %d steps!\n", steps);

    // cleanup
    for (int i = 0; i < NUM_TOWERS; i++)
        free_stack(towers[i]);

    return 0;
}

void print_towers(struct Stack **towers)
{
    for (int i = 0; i < NUM_TOWERS; i++)
    {
        printf("%2d -> ", i);
        print_stack(towers[i]);
    }
    printf("--------------\n");
}

bool is_final_state(struct Stack **towers)
{
    for (int i = 0; i < NUM_TOWERS - 1; i++)
        if (!is_empty_stack(towers[i]))
            return 0;

    struct StackItem *item = towers[NUM_TOWERS - 1]->top;
    for (int v = 1; v <= NUM_DISCS; v++)
    {
        if (item == NULL)
            return 0;

        if (item->value != v)
            return 0;

        item = item->next;
    }

    return 1;
}

void move_smallest(struct Stack **towers)
{
    for (int i = 0; i < NUM_TOWERS; i++)
    {
        if (!is_empty_stack(towers[i]) && towers[i]->top->value == 1)
        {
            int v = pop_stack(towers[i]);

            // even, move right
            if (NUM_DISCS % 2 == 0)
            {
                if (i + 1 < NUM_TOWERS)
                {
                    push_stack(towers[i + 1], v);
                }
                else
                {
                    push_stack(towers[0], v);
                }
            }
            // odd, move left
            else
            {
                if (i - 1 > 0)
                {
                    push_stack(towers[i - 1], v);
                }
                else
                {
                    push_stack(towers[NUM_TOWERS - 1], v);
                }
            }

            break;
        }
    }
}

void move_non_smallest(struct Stack **towers)
{
    int target = -1;

    for (int i = 0; i < NUM_TOWERS; i++)
    {
        // find non-smallest candidate
        if (!is_empty_stack(towers[i]) && towers[i]->top->value != 1)
        {
            int v = towers[i]->top->value;
            // try and find a home
            for (int j = 0; j < NUM_TOWERS; j++)
            {
                if (i == j)
                    continue;

                // this is a home1
                if (is_empty_stack(towers[j]) || towers[j]->top->value > v)
                {
                    target = j;
                    break;
                }
            }
        }

        // if we found a home, we're done, move piece and return
        if (target != -1)
        {
            push_stack(towers[target], pop_stack(towers[i]));
            return;
        }
    }

    printf("Error! Illegal state. Aborting!\n");
    exit(1);
}
