#include "render.h"

#include <math.h>
#include <stdio.h>

#include "constants.h"
#include "raylib.h"
#include "data/grid.h"
#include "data/player.h"


void Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawMap();

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
    const auto playerGridPositionX = player.position.x / TILE_SIZE;
    const auto playerGridPositionY = player.position.y / TILE_SIZE;
    const auto playerPositionX = mapXOffset + playerGridPositionX * MINIMAP_TILE_SIZE;
    const auto playerPositionY = playerGridPositionY * MINIMAP_TILE_SIZE;

    DrawCircle((int)playerPositionX, (int)playerPositionY, player.radius, RED);
    DrawLineEx((Vector2){playerPositionX, playerPositionY}, (Vector2){playerPositionX + (float)(cos(player.rotation) * MINIMAP_TILE_SIZE * 2), playerPositionY + (float)(sin(player.rotation) * MINIMAP_TILE_SIZE * 2)}, 1.5f, RED);
}
