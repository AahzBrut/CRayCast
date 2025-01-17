#include "update.h"

#include "data/player.h"

void Update(const float deltaTime) {
    player.position.x += player.walkSpeed * deltaTime;
    player.position.y += player.walkSpeed * deltaTime;
}
