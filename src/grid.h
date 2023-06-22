#ifndef _grid_h_
#define _grid_h_

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t cell_t[10];

typedef struct grid_t {
    cell_t row[9][9];
    cell_t col[9][9];
    cell_t box[9][9];
} grid_t;

grid_t grid_load(char str[9*9]);
void grid_set(grid_t *grid, int x, int y, uint8_t number);
void grid_copy_cell(grid_t grid, cell_t *dst, int x, int y);
void grid_draw(grid_t grid);

#endif

