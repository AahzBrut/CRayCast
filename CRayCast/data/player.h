#pragma once
#include "raylib.h"

typedef struct Player {
    Vector2 position;
    float radius;
    float walkSpeed;
    float turnSpeed;
    int turnDirection;
    int walkDirection;
    float rotation;
} Player;

extern Player player;
