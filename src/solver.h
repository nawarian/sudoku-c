#ifndef _solver_h_
#define _solver_h_

#include "grid.h"

grid_t solver_pass(grid_t grid);

typedef grid_t (*solver_function)(grid_t);
grid_t solver_single_possibilities(grid_t grid);

#endif

