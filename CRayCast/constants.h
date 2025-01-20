#pragma once
#include <math.h>
#include <raylib.h>

#define TWO_PI (PI * 2)

#define TILE_SIZE 64
#define MINIMAP_TILE_SIZE 16
#define GRID_ROW_COUNT 13
#define GRID_COL_COUNT 20

#define WINDOW_WIDTH (TILE_SIZE * GRID_COL_COUNT)
#define WINDOW_HEIGHT (TILE_SIZE * GRID_ROW_COUNT)
#define MINIMAP_X_OFFSET (WINDOW_WIDTH - GRID_COL_COUNT * MINIMAP_TILE_SIZE)

#define FOV (60 * DEG2RAD)
#define NUM_RAYS WINDOW_WIDTH
#define PROJ_PLANE_DISTANCE (WINDOW_WIDTH * tanf(FOV * 0.5f))

#define NUM_TEXTURES 8
