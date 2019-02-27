//
// Created by Nick Codignotto on 2019-02-26.
//

#ifndef HANOI_ITERATIVE_H
#define HANOI_ITERATIVE_H

#include "stack.h"

#define NUM_TOWERS 3

struct Hanoi {
    int numDiscs;
    struct Stack *towers[NUM_TOWERS];
};

void solve_iterative(int numDiscs);

struct Hanoi* allocate_hanoi(int numDiscs);
void free_hanoi(struct Hanoi* h);

void print_towers(struct Hanoi* h);
bool is_final_state(struct Hanoi* h);
void move_smallest(struct Hanoi* h);
void move_non_smallest(struct Hanoi* h);

#endif //HANOI_ITERATIVE_H
