#include "render.h"

#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "constants.h"
#include "data/grid.h"
#include "data/player.h"
#include "data/ray.h"


void Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawMap();
    DrawPlayer();
    DrawRays();

    RenderFPSCount();

    EndDrawing();
}

void RenderFPSCount() {
    char stringBuffer[16];
    sprintf(&stringBuffer[0], "%d", GetFPS());
    DrawText(stringBuffer, 5, 5, 32, WHITE);
}

void DrawPlayer() {
    const auto playerGridPositionX = player.position.x / TILE_SIZE;
    const auto playerGridPositionY = player.position.y / TILE_SIZE;
    const auto playerPositionX = MINIMAP_X_OFFSET + playerGridPositionX * MINIMAP_TILE_SIZE;
    const auto playerPositionY = playerGridPositionY * MINIMAP_TILE_SIZE;

    DrawCircle((int)playerPositionX, (int)playerPositionY, player.radius, RED);
    DrawLineEx((Vector2){playerPositionX, playerPositionY}, (Vector2){playerPositionX + (float)(cos(player.rotation) * MINIMAP_TILE_SIZE * 2), playerPositionY + (float)(sin(player.rotation) * MINIMAP_TILE_SIZE * 2)}, 1.5f, RED);
}

void DrawMap() {
    for (auto row = 0; row < GRID_ROW_COUNT; row++) {
        for (auto col = 0; col < GRID_COL_COUNT; col++) {
            if (grid[row][col] != 0) {
                DrawRectangle(MINIMAP_X_OFFSET + col * MINIMAP_TILE_SIZE, row * MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, BLUE);
            } else {
                DrawRectangle(MINIMAP_X_OFFSET + col * MINIMAP_TILE_SIZE, row * MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE, WHITE);
            }
        }
    }
}

void DrawRays() {
    const auto playerGridPositionX = player.position.x / TILE_SIZE;
    const auto playerGridPositionY = player.position.y / TILE_SIZE;
    const auto playerPositionX = MINIMAP_X_OFFSET + playerGridPositionX * MINIMAP_TILE_SIZE;
    const auto playerPositionY = playerGridPositionY * MINIMAP_TILE_SIZE;

    for (auto index = 0; index < NUM_RAYS; index++) {
        const auto hitGridPositionX = rays[index].wallHitPosition.x / TILE_SIZE;
        const auto hitGridPositionY = rays[index].wallHitPosition.y / TILE_SIZE;
        const auto hitPositionX = MINIMAP_X_OFFSET + hitGridPositionX * MINIMAP_TILE_SIZE;
        const auto hitPositionY = hitGridPositionY * MINIMAP_TILE_SIZE;

        DrawLine((int)playerPositionX, (int)playerPositionY, (int)hitPositionX, (int)hitPositionY, RED);
    }
}
