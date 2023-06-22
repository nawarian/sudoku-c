#include <math.h>
#include <raylib.h>

#include "grid.h"
#include "globals.h"

void _idx_to_x_y(int idx, int *x, int *y)
{
    *y = (int) (idx / 9);
    *x = idx - (*y * 9);
}

void _draw_small_text(int x, int y, int number);

grid_t grid_load(char matrix[9*9])
{
    char chr;
    uint8_t val;
    int x, y;

    grid_t grid = { 0 };
    for (int i = 0; i < 81; ++i) {
        _idx_to_x_y(i, &x, &y);
        chr = matrix[i];
        val = chr - 48; // ASCII to DEC

        if (chr < '0' || chr > '9') {
            TraceLog(LOG_FATAL,
                    "Invalid character %d at pos %d - %c",
                    val, i, chr);
        }

        for (int j = 1; j < 10; ++j) {
            grid.matrix[x][y][j] = 0;
            if (chr == '0') {
                grid.matrix[x][y][j] = 1;
            }
        }

        if (chr != '0') {
            grid.matrix[x][y][0] = val;
        }
   }

    return grid;
}

void grid_draw(grid_t grid)
{
    int x, y;
    int i;

    // Draw cells
    const char *buff;
    int coord_x, coord_y;
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

            if (grid.matrix[x][y][0] > 0) {
                DrawRectangle(
                    coord_x + 1,
                    coord_y + 1,
                    CELL_WIDTH,
                    CELL_HEIGHT,
                    DARKGRAY);

                buff = TextFormat("%d", grid.matrix[x][y][0]);
                DrawText(buff,
                        coord_x + (CELL_WIDTH / 2),
                        coord_y + (CELL_HEIGHT / 3),
                        CELL_HEIGHT / 3,
                        LIGHTGRAY);
            } else {
                // Draw subgrid
                for (i = 1; i < 10; ++i) {
                    if (grid.matrix[x][y][i] > 0) {
                        _draw_small_text(x, y, i);
                    }
                }
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

void _draw_small_text(int x, int y, int number)
{
    int origin_x, origin_y, width = CELL_WIDTH / 3, height = CELL_HEIGHT / 3;
    int cell_x, cell_y;

    origin_x = GRID_MARGIN + (CELL_WIDTH * x) + x;
    cell_x = origin_x;
    cell_x += width / 4;

    origin_y = GRID_MARGIN + (CELL_HEIGHT * y) + y;
    cell_y = origin_y;
    cell_y += height / 4;

    switch (number) {
        case 4: case 5: case 6:
            cell_y += height;
            break;
        case 7: case 8: case 9:
            cell_y += height * 2;
            break;
    }

    switch (number) {
        case 2: case 5: case 8:
            cell_x += width;
            cell_x += width / 4;
            cell_x -= width / 8;
            break;
        case 3: case 6: case 9:
            cell_x += width * 2;
            cell_x -= width / 8;
            cell_x += width / 2;
            break;
    }

    const char *buff = TextFormat("%d", number);
    DrawText(buff, cell_x, cell_y, height / 4, LIGHTGRAY);
}

