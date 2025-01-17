#include <raylib.h>

#include "constants.h"
#include "game_loop/process_input.h"
#include "game_loop/render.h"
#include "game_loop/update.h"
#include "init/initialize.h"


int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RayCast Demo");
    SetTargetFPS(60);

    Initialize();

    while (!WindowShouldClose()) {
        ProcessInput();
        Update(GetFrameTime());
        Render();
    }

    CloseWindow();
    return 0;
}
