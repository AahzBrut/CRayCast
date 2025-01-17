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
    for (auto row = 0; row < MAP_ROW_COUNT; row++) {
        for (auto col = 0; col < MAP_COL_COUNT; col++) {
            if (grid[row][col] != 0) {
                DrawRectangle(WINDOW_WIDTH - 8 - col * 8, row * 8, 8, 8, BLUE);
            } else {
                DrawRectangle(WINDOW_WIDTH - 8 - col * 8, row * 8, 8, 8, WHITE);
            }
        }
    }
}
