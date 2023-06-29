#include <raylib.h>
#include <stdbool.h>
#include "solver.h"

solver_function solver_strategies[] = {
    solver_naked_single,
    solver_backtrack
};

const char* solver_strategy_get(int idx)
{
    switch (idx) {
        case 0: return "Naked single";
        case 1: return "Backtracking";
        default: return "Unknown";
    }
}

solver_pass_t solver_pass(grid_t grid)
{
    solver_pass_t res;
    res.strategy = -1;

    int solver_count = sizeof(solver_strategies) / sizeof(solver_function);
    for (int i = 0; i < solver_count; ++i) {
        res = solver_strategies[i](grid);
        if (res.applied) {
            res.strategy = i;
            grid = grid_cleanup(res.result);
            return res;
        }
    }

    res.result = grid;
    res.applied = false;
    return res;
}

solver_pass_t solver_naked_single(grid_t grid)
{
    solver_pass_t res = (solver_pass_t) {
        false,
        -1,
        grid
    };

    cell_t *cell;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            uint8_t val = grid.cell[row][col][0];
            cell = &grid.cell[row][col];

            // If value is set, ignore
            if (val > 0) {
                continue;
            }

            // How many possibilities this cell has
            int acc = 0;
            for (int i = 1; i < 10; ++i) {
                if (grid.cell[row][col][i] == 1) {
                    acc++;
                }
            }

            // If more than one, ignore
            if (acc != 1) {
                continue;
            }

            for (int i = 1; i < 10; ++i) {
                if (grid.cell[row][col][i] == 1) {
                    grid_set(&grid, col, row, i);
                    res.applied = true;
                    res.result = grid;
                }
            }
        }
    }

    return res;
}

solver_pass_t solver_backtrack(grid_t grid)
{
    solver_pass_t pass;
    pass.applied = false;
    pass.result = grid;

    return pass;
}

