#include "initialize.h"

#include "constants.h"
#include "data/player.h"

void Initialize() {
    player.position = (Vector2){(float)WINDOW_WIDTH / 2,(float)WINDOW_HEIGHT / 2};
    player.walkSpeed = 60;
    player.radius = 4;
    player.rotation = 0;
    player.turnDirection = 0;
    player.turnSpeed = 45 * DEG2RAD;
    player.walkDirection = 0;
    player.walkSpeed = 60;
}
