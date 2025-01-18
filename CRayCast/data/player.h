#pragma once
#include "raylib.h"

extern struct Player {
    Vector2 position;
    float radius;
    float walkSpeed;
    float turnSpeed;
    int turnDirection;
    int walkDirection;
    float rotation;
} player;

void MovePlayer(float deltaTime);