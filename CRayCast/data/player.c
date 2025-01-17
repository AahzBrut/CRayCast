#include "data/player.h"

#include <tgmath.h>

#include "data/grid.h"

struct Player player;

void MovePlayer(const float deltaTime) {
    player.rotation += player.turnSpeed * (float)player.turnDirection * deltaTime;

    const auto newPlayerX = player.position.x + player.walkSpeed * (float)player.walkDirection * (float)cos(player.rotation) * deltaTime;
    const auto newPlayerY = player.position.y + player.walkSpeed * (float)player.walkDirection * (float)sin(player.rotation) * deltaTime;

    if (HasWallAtGridPosition(newPlayerX, newPlayerY)) {
        player.position.x = newPlayerX;
        player.position.y = newPlayerY;
    }
}
