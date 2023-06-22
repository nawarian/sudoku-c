#include <math.h>
#include <string.h>
#include <raylib.h>

#include "grid.h"
#include "globals.h"

void _idx_to_xy(int idx, int *x, int *y)
{
    *y = (int) (idx / 9);
    *x = idx - (*y * 9);
}

uint8_t _xy_to_box(int x, int y)
{
    x = floor(x / 3);
    y = floor(y / 3);

    return (uint8_t) (x + (y * x));
}

void _draw_small_text(int x, int y, int number);

void grid_set(grid_t *grid, int x, int y, uint8_t number)
{
    uint8_t bid = _xy_to_box(x, y);

    for (int i = 1; i < 10; ++i) {
        grid->col[x][y][i] = number > 0 ? 0 : 1;
        grid->row[y][x][i] = number > 0 ? 0 : 1;
        grid->box[bid][i] = number > 0 ? 0 : 1;
    }

    if (number > 0) {
        grid->col[x][y][0] = number;
        grid->col[x][y][number] = 1;

        grid->row[y][x][0] = number;
        grid->row[y][x][number] = 1;

        grid->box[bid][0] = number;
        grid->box[bid][number] = number;
    }
}

void grid_cell_copy(grid_t grid, cell_t *dst, int x, int y)
{
    memcpy(dst, &grid.col[x][y], sizeof(cell_t));
}

grid_t grid_load(char matrix[9*9])
{
    char chr;
    uint8_t val;
    int x, y;

    grid_t grid = { 0 };
    for (int i = 0; i < 81; ++i) {
        _idx_to_xy(i, &x, &y);
        chr = matrix[i];
        val = chr - 48; // ASCII to DEC

        if (chr < '0' || chr > '9') {
            TraceLog(LOG_FATAL,
                    "Invalid character %d at pos %d - %c",
                    val, i, chr);
        }

        grid_set(&grid, x, y, val > 0 ? val : 0);
    }

    return grid_cleanup(grid);
}


void grid_cell_remove_possibility(grid_t *grid, int x, int y, uint8_t val)
{
    uint8_t bid = _xy_to_box(x, y);
    grid->box[bid][val] = 0;

    for (int i = 0; i < 9; ++i) {
        if (i != y) {
            grid->row[i][x][val] = 0;
            grid->col[x][i][val] = 0;
        }
    }
}

grid_t grid_cleanup(grid_t g)
{
    cell_t cell;
    uint8_t val, bid;
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            grid_cell_copy(g, &cell, x, y);
            val = cell[0];

            // Remove possibilities
            if (val > 0) {
                grid_cell_remove_possibility(&g, x, y, val);
            }
        }
    }

    return g;
}

void grid_draw(grid_t grid)
{
    int x, y;
    int i;

    // Draw cells
    const char *buff;
    int coord_x, coord_y;
    cell_t cell;
    for (y = 0; y < 9; ++y) {
        for (x = 0; x < 9; ++x) {
            grid_cell_copy(grid, &cell, x, y);

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

            if (cell[0] > 0) {
                DrawRectangle(
                    coord_x + 1,
                    coord_y + 1,
                    CELL_WIDTH,
                    CELL_HEIGHT,
                    DARKGRAY);

                buff = TextFormat("%d", cell[0]);
                DrawText(buff,
                        coord_x + (CELL_WIDTH / 2),
                        coord_y + (CELL_HEIGHT / 3),
                        CELL_HEIGHT / 3,
                        LIGHTGRAY);
            } else {
                // Draw subgrid
                for (i = 1; i < 10; ++i) {
                    if (cell[i] > 0) {
                        _draw_small_text(x, y, i);
                    }
                }
            }
        }
    }

    // Draw boxes
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

