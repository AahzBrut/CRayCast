#include "initialize.h"

#include <stdlib.h>

#include "constants.h"
#include "data/player.h"

void Initialize() {
    player.position = (Vector2){(float) WINDOW_WIDTH / 2, (float) WINDOW_HEIGHT / 2};
    player.walkSpeed = 60;
    player.radius = 4;
    player.rotation = PI / 2;
    player.turnDirection = 0;
    player.turnSpeed = PI / 3;
    player.walkDirection = 0;
    player.walkSpeed = 100;
}

void DeInitialize() {
}
