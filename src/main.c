#include <raylib.h>

#include "grid.h"
#include "globals.h"

int main(void)
{
/*  6, 9, 0,  8, 0, 5,  7, 3, 0,
    5, 1, 8,  7, 6, 3,  0, 2, 0,
    3, 7, 4,  1, 9, 2,  6, 8, 0,

    0, 0, 7,  9, 5, 4,  3, 1, 2,
    9, 3, 0,  2, 1, 7,  0, 4, 6,
    4, 2, 1,  6, 3, 8,  9, 0, 0,

    0, 5, 6,  3, 8, 1,  2, 9, 4,
    0, 4, 0,  5, 7, 9,  1, 6, 8,
    0, 8, 9,  4, 0, 6,  0, 7, 3  */
    char matrix[9*9] = "690805730518763020374192680007954312930217046421638900056381294040579168089406073";

    grid_t grid = grid_load(matrix);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku C");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        grid = grid_cleanup(grid);

        ClearBackground(BLACK);
        BeginDrawing();
            grid_draw(grid);

            DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

