#include "data/player.h"

#include <math.h>

#include "data/grid.h"

struct Player player;

void MovePlayer(const float deltaTime) {
    player.rotation += player.turnSpeed * (float)player.turnDirection * deltaTime;

    const auto newPlayerX = player.position.x + player.walkSpeed * (float)player.walkDirection * cosf(player.rotation) * deltaTime;
    const auto newPlayerY = player.position.y + player.walkSpeed * (float)player.walkDirection * sinf(player.rotation) * deltaTime;

    if (!HasWallAtGridPosition(newPlayerX, newPlayerY)) {
        player.position.x = newPlayerX;
        player.position.y = newPlayerY;
    }
}
