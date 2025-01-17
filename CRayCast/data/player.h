#pragma once
#include "raylib.h"

extern struct Player {
    Vector2 position;
    float radius;
    float walkSpeed;
    float turnSpeed;
    int turnDirection;
    int walkDirection;
    double rotation;
} player;

void MovePlayer(float deltaTime);