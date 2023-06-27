#include <raylib.h>
#include <string.h>

#include "grid.h"
#include "solver.h"
#include "globals.h"

int main(int argc, const char **argv)
{
    if (argc < 2) {
        TraceLog(LOG_FATAL, "Usage: solver solver-string");
    }

    char matrix[9*9];
    memcpy(matrix, argv[1], sizeof(matrix));

    grid_t grid = grid_load(matrix);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku C");
    SetTargetFPS(60);

    solver_pass_t res;
    while(!WindowShouldClose()) {
        grid = grid_cleanup(grid);

        if (IsKeyPressed(KEY_SPACE)) {
            res = solver_pass(grid);

            if (res.applied) {
                grid = res.result;
            }
        }

        ClearBackground(BLACK);
        BeginDrawing();
            grid_draw(grid);

            DrawFPS(0, 0);
            if (res.applied) {
                DrawText(TextFormat("Strategy %s applied", solver_strategy_get(res.strategy)),
                        0, SCREEN_HEIGHT - 20, 20, GREEN);
            } else {
                DrawText("No strategies applied.", 0, SCREEN_HEIGHT - 20, 20, RED);
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

