#include <raylib.h>

#include "constants.h"

void Render();
void Update();
void ProcessInput();

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RayCast Demo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ProcessInput();
        Update();
        Render();
    }

    CloseWindow();
    return 0;
}

void ProcessInput() {

}

void Update() {

}

void Render() {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}