#include "update.h"

#include "data/player.h"
#include "data/ray.h"

void Update(const float deltaTime) {
    MovePlayer(deltaTime);
    CastAllRays();
}
