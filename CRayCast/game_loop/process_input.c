#include "process_input.h"

#include "raylib.h"
#include "data/player.h"


void ProcessInput() {
    player.turnDirection =  IsKeyDown(KEY_A) ? -1 : IsKeyDown(KEY_D) ? 1 : 0;
    player.walkDirection =  IsKeyDown(KEY_S) ? -1 : IsKeyDown(KEY_W) ? 1 : 0;
}
