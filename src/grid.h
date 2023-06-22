#ifndef _grid_h_
#define _grid_h_

#include <stdbool.h>
#include <stdint.h>

typedef struct grid_t {
    uint8_t matrix[9][9][10];
} grid_t;

grid_t grid_load(char str[9*9]);
void grid_draw(grid_t grid);

#endif

