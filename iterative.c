//
// Created by Nick Codignotto on 2019-02-26.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "iterative.h"
#include "stack.h"

struct Hanoi* allocate_hanoi(int numDiscs) {
    struct Hanoi* h = (struct Hanoi*)malloc(sizeof(struct Hanoi));

    for (int i=0; i < 3; i++)
        h->towers[i] = allocate_stack();

    // initialize
    for (int i = numDiscs; i > 0; i--)
        push_stack(h->towers[0], i);

    return h;
}

void free_hanoi(struct Hanoi* h) {
    for (int i=0; i < 3; i++)
        free_stack(h->towers[i]);
}

void solve_iterative(int numDiscs) {

    struct Hanoi* hanoi = allocate_hanoi(numDiscs);

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
    print_towers(hanoi);
    move_smallest(hanoi);

    while (!is_final_state(hanoi))
    {
        move_non_smallest(hanoi);
        print_towers(hanoi);
        move_smallest(hanoi);
        print_towers(hanoi);
        steps += 2;
    }

    printf("Finished in %d steps!\n", steps);

    free_hanoi(hanoi);
}

void print_towers(struct Hanoi* h)
{
    for (int i = 0; i < NUM_TOWERS; i++)
    {
        printf("%2d -> ", i);
        print_stack(h->towers[i]);
    }
    printf("--------------\n");
}

bool is_final_state(struct Hanoi* h)
{
    for (int i = 0; i < NUM_TOWERS - 1; i++)
        if (!is_empty_stack(h->towers[i]))
            return 0;

    struct StackItem *item = h->towers[NUM_TOWERS - 1]->top;
    for (int v = 1; v <= h->numDiscs; v++)
    {
        if (item == NULL)
            return 0;

        if (item->value != v)
            return 0;

        item = item->next;
    }

    return 1;
}

void move_smallest(struct Hanoi* h)
{
    for (int i = 0; i < NUM_TOWERS; i++)
    {
        if (!is_empty_stack(h->towers[i]) && h->towers[i]->top->value == 1)
        {
            int v = pop_stack(h->towers[i]);

            // even, move right
            if (h->numDiscs % 2 == 0)
            {
                if (i + 1 < NUM_TOWERS)
                {
                    push_stack(h->towers[i + 1], v);
                }
                else
                {
                    push_stack(h->towers[0], v);
                }
            }
                // odd, move left
            else
            {
                if (i - 1 > 0)
                {
                    push_stack(h->towers[i - 1], v);
                }
                else
                {
                    push_stack(h->towers[NUM_TOWERS - 1], v);
                }
            }

            break;
        }
    }
}

void move_non_smallest(struct Hanoi* h)
{
    int target = -1;

    for (int i = 0; i < NUM_TOWERS; i++)
    {
        // find non-smallest candidate
        if (!is_empty_stack(h->towers[i]) && h->towers[i]->top->value != 1)
        {
            int v = h->towers[i]->top->value;
            // try and find a home
            for (int j = 0; j < NUM_TOWERS; j++)
            {
                if (i == j)
                    continue;

                // this is a home1
                if (is_empty_stack(h->towers[j]) || h->towers[j]->top->value > v)
                {
                    target = j;
                    break;
                }
            }
        }

        // if we found a home, we're done, move piece and return
        if (target != -1)
        {
            push_stack(h->towers[target], pop_stack(h->towers[i]));
            return;
        }
    }

    printf("Error! Illegal state. Aborting!\n");
    exit(1);
}
