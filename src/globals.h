#ifndef _globals_h_
#define _globals_h_


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GRID_MARGIN 50
#define GRID_WIDTH (SCREEN_WIDTH - GRID_MARGIN * 2)
#define GRID_HEIGHT (SCREEN_HEIGHT - GRID_MARGIN * 2)

#define BLOCK_WIDTH (int) (GRID_WIDTH / 3)
#define BLOCK_HEIGHT (int) (GRID_HEIGHT / 3)

#define CELL_WIDTH (int) (BLOCK_WIDTH / 3)
#define CELL_HEIGHT (int) (BLOCK_HEIGHT / 3)

#endif

