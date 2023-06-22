#include <raylib.h>

#include "grid.h"
#include "globals.h"

int _idx_at(int x, int y)
{
    return x + y * 9;
}

grid_t grid_load(char matrix[9*9])
{
    grid_t grid;
    int val;
    for (int i = 0; i < 81; ++i) {
        val = matrix[i] - 48; // ASCII to DEC
        if (val < 0 || val > 9) {
            TraceLog(LOG_FATAL,
                    "Invalid character %d at pos %d - %c",
                    val, i, matrix[i]);
        }

        grid.matrix[i] = val;
    }

    return grid;
}

bool grid_is_busy(grid_t grid, int x, int y)
{
    int idx = _idx_at(x, y);

    return grid.matrix[idx] > 0;
}

void grid_draw(grid_t grid)
{
    int x, y;

    // Draw cells
    const char *buff;
    int coord_x, coord_y;
    int cell_value = 0;
    for (y = 0; y < 9; ++y) {
        for (x = 0; x < 9; ++x) {
            coord_x = GRID_MARGIN +
                (CELL_WIDTH * x) + x;
            coord_y = GRID_MARGIN +
                (CELL_HEIGHT * y) + y;
            DrawRectangleLines(
                    coord_x,
                    coord_y,
                    CELL_WIDTH + 2,
                    CELL_HEIGHT + 2,
                    GRAY);

            cell_value = grid.matrix[_idx_at(x, y)];
            if (cell_value > 0) {
                DrawRectangle(
                    coord_x + 1,
                    coord_y + 1,
                    CELL_WIDTH,
                    CELL_HEIGHT,
                    DARKGRAY);

                buff = TextFormat("%d", cell_value);
                DrawText(buff,
                        coord_x + (CELL_WIDTH / 2),
                        coord_y + (CELL_HEIGHT / 3),
                        CELL_HEIGHT / 3,
                        LIGHTGRAY);
            }
        }
    }

    // Draw blocks
    for (y = 0; y < 3; ++y) {
        for (x = 0; x < 3; ++x) {
            DrawRectangleLines(
                    GRID_MARGIN +
                        (BLOCK_WIDTH * x) + x + 1,
                    GRID_MARGIN +
                        (BLOCK_HEIGHT * y) + y + 1,
                    BLOCK_WIDTH + 2,
                    BLOCK_HEIGHT + 2,
                    LIGHTGRAY);
        }
    }

}

