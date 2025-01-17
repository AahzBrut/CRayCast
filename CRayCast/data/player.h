#pragma once
#include "raylib.h"

struct Player {
    Vector2 position;
    float radius;
    float walkSpeed;
    float turnSpeed;
    int turnDirection;
    int walkDirection;
    double rotation;
};

extern struct Player player;

void MovePlayer(float deltaTime);