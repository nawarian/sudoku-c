#include <raylib.h>
#include "solver.h"

solver_function solver_strategies[] = {
    solver_naked_single,
};

grid_t solver_pass(grid_t grid)
{
    int solver_count = sizeof(solver_strategies) / sizeof(solver_function);
    for (int i = 0; i < solver_count; ++i) {
        grid = solver_strategies[i](grid);
        grid = grid_cleanup(grid);
    }

    return grid;
}

grid_t solver_naked_single(grid_t grid)
{
    cell_t *cell;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            uint8_t val = grid_cell_get(grid, col, row);
            cell = &grid.row[row][col];

            // If value is set, ignore
            if (val > 0) {
                continue;
            }

            // How many possibilities this cell has
            int acc = 0;
            for (int i = 1; i < 10; ++i) {
                if (grid.row[row][col][i] == 1) {
                    acc++;
                }
            }

            // If more than one, ignore
            if (acc != 1) {
                continue;
            }

            for (int i = 1; i < 10; ++i) {
                if (grid.row[row][col][i] == 1) {
                    grid_set(&grid, col, row, i);
                }
            }
        }
    }

    return grid;
}

