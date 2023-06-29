#ifndef _solver_h_
#define _solver_h_

#include "grid.h"
#include <stdbool.h>

typedef struct solver_pass_t {
    bool applied;
    int strategy;
    grid_t result;
} solver_pass_t;

solver_pass_t solver_pass(grid_t grid);

typedef solver_pass_t (*solver_function)(grid_t);
solver_pass_t solver_naked_single(grid_t grid);
solver_pass_t solver_backtrack(grid_t grid);
const char* solver_strategy_get(int idx);

#endif

