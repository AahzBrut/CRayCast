#include "update.h"

#include <math.h>

#include "data/player.h"

void Update(const float deltaTime) {
    player.rotation += player.turnSpeed * (float)player.turnDirection * deltaTime;
    player.position.x += player.walkSpeed * (float)player.walkDirection * (float)cos(player.rotation) * deltaTime;
    player.position.y += player.walkSpeed * (float)player.walkDirection * (float)sin(player.rotation) * deltaTime;
}
