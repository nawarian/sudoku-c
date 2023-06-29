#ifndef _grid_h_
#define _grid_h_

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t cell_t[10];

typedef struct grid_t {
    cell_t cell[9][9];
} grid_t;

grid_t grid_load(char str[9*9]);
grid_t grid_cleanup(grid_t g);
bool grid_can_set(grid_t grid, int x, int y, uint8_t value);
void grid_set(grid_t *grid, int x, int y, uint8_t number);
void grid_cell_remove_possibility(grid_t *grid, int x, int y, uint8_t val);

void grid_draw(grid_t grid);

#endif

