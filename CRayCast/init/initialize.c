#include "initialize.h"

#include <stdlib.h>

#include "constants.h"
#include "data/player.h"
#include "game_loop/render.h"

void Initialize() {
    player.position = (Vector2){(float) WINDOW_WIDTH / 2, (float) WINDOW_HEIGHT / 2};
    player.walkSpeed = 60;
    player.radius = 4;
    player.rotation = PI / 2;
    player.turnDirection = 0;
    player.turnSpeed = PI / 3;
    player.walkDirection = 0;
    player.walkSpeed = 100;

    wallTextures[0] = LoadTexture("./assets/Brick_Wall_64x64.png");
    wallTextures[1] = LoadTexture("./assets/Brick_Wall_Cracked_64x64.png");
    wallTextures[2] = LoadTexture("./assets/Grass_64x64.png");
    wallTextures[3] = LoadTexture("./assets/Green_Wall_Rocks_64x64.png");
    wallTextures[4] = LoadTexture("./assets/Magma_Floor_64x64.png");
    wallTextures[5] = LoadTexture("./assets/Rocky_Road_64x64.png");
    wallTextures[6] = LoadTexture("./assets/Wooden_Floor_Horizontal_64x64.png");
    wallTextures[7] = LoadTexture("./assets/Wooden_Floor_Vertical_64x64.png");
}

void DeInitialize() {
    for (auto i = 0; i < NUM_TEXTURES; i++) {
        UnloadTexture(wallTextures[i]);
    }
}
