#include "render.h"

#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "constants.h"
#include "data/grid.h"
#include "data/player.h"
#include "data/ray.h"

Texture2D wallTexture;
// ReSharper disable once CppUseAutoForNumeric
bool renderTextured = false;

void Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    RenderWorld();

    DrawMap();
    DrawRays();
    DrawPlayer();

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

    DrawCircle((int) playerPositionX, (int) playerPositionY, player.radius, BLUE);
    DrawLineEx((Vector2){playerPositionX, playerPositionY}, (Vector2){
                   playerPositionX + cosf(player.rotation) * MINIMAP_TILE_SIZE * 2,
                   playerPositionY + sinf(player.rotation) * MINIMAP_TILE_SIZE * 2
               }, 1.5f, BLUE);
}

void RenderWorld() {
    for (auto index = 0; index < NUM_RAYS; index++) {
        const auto ray = rays[index];
        const auto correctedDistance = ray.distance * cosf(ray.angle - player.rotation);
        const auto distanceToProjPlane = (float) WINDOW_WIDTH / 2.f * tanf(FOV / 2.f);
        const auto projectedWallHeight = TILE_SIZE / correctedDistance * distanceToProjPlane;
        const auto wallTopPixel = WINDOW_HEIGHT / 2 - (int) projectedWallHeight / 2;
        const auto scaledWallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
        const auto wallBottomPixel = WINDOW_HEIGHT / 2 + (int) projectedWallHeight / 2;
        const auto scaledWallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;
        const auto skyColor = BLUE;
        const auto floorColor = DARKGRAY;
        if (wallTopPixel > 0) DrawLine(index, 0, index, wallTopPixel, skyColor);
        if (!renderTextured) {
            const auto wallColor = ray.isHitVertical ? WHITE : LIGHTGRAY;
            DrawLine(index, scaledWallTopPixel, index, scaledWallBottomPixel, wallColor);
        } else {
            const auto wallColor = ray.isHitVertical ? WHITE : LIGHTGRAY;
            const auto textureOffsetX = ray.isHitVertical ? (int)ray.wallHitPosition.y % TILE_SIZE : (int)ray.wallHitPosition.x % TILE_SIZE;
            const auto sourceRect = (Rectangle){(float)textureOffsetX, 0, 1, TILE_SIZE};
            const auto targetRect = (Rectangle){(float)index, (float)wallTopPixel, 1, (float)wallBottomPixel - (float)wallTopPixel};
            DrawTexturePro(wallTexture, sourceRect, targetRect, (Vector2){0,0}, 0, wallColor);
        }
        if (wallBottomPixel < WINDOW_HEIGHT) DrawLine(index, wallBottomPixel, index, WINDOW_HEIGHT, floorColor);
    }
}

void DrawMap() {
    for (auto row = 0; row < GRID_ROW_COUNT; row++) {
        for (auto col = 0; col < GRID_COL_COUNT; col++) {
            if (grid[row][col] != 0) {
                DrawRectangle(MINIMAP_X_OFFSET + col * MINIMAP_TILE_SIZE, row * MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE,
                              MINIMAP_TILE_SIZE, BLUE);
            } else {
                DrawRectangle(MINIMAP_X_OFFSET + col * MINIMAP_TILE_SIZE, row * MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE,
                              MINIMAP_TILE_SIZE, WHITE);
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

        DrawLine((int) playerPositionX, (int) playerPositionY, (int) hitPositionX, (int) hitPositionY, RED);
    }
}
