#ifndef _grid_h_
#define _grid_h_

#include <stdbool.h>

typedef struct grid_t {
    char matrix[9*9];
} grid_t;

bool grid_is_busy(grid_t grid, int x, int y);
void grid_draw(grid_t grid);

#endif

