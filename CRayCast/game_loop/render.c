#include "render.h"
#include <stdio.h>

#include "constants.h"
#include "raylib.h"
#include "data/grid.h"
#include "data/player.h"


void Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawMap();

    DrawRectangleV(player.position, (Vector2){64, 64}, RED);

    RenderFPSCount();

    EndDrawing();
}

void RenderFPSCount() {
    char stringBuffer[16];
    sprintf(&stringBuffer[0], "%d", GetFPS());
    DrawText(stringBuffer, 5, 5, 32, WHITE);
}

void DrawMap() {
    constexpr auto mapXOffset = WINDOW_WIDTH - GRID_COL_COUNT * MINIMAP_TILE_SIZE;
    for (auto row = 0; row < GRID_ROW_COUNT; row++) {
        for (auto col = 0; col < GRID_COL_COUNT; col++) {
            if (grid[row][col] != 0) {
                DrawRectangle(mapXOffset + col * MINIMAP_TILE_SIZE, row * MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, BLUE);
            } else {
                DrawRectangle(mapXOffset + col * MINIMAP_TILE_SIZE, row * MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, WHITE);
            }
        }
    }
    const auto playerGridPositionX = (int)player.position.x / TILE_SIZE;
    const auto playerGridPositionY = (int)player.position.y / TILE_SIZE;

    DrawCircle(mapXOffset + playerGridPositionX * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2, playerGridPositionY * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2, player.radius, RED);
}
