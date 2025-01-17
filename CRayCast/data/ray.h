#pragma once
#include <raylib.h>
#include "constants.h"

extern struct RayCast {
    float angle;
    Vector2 wallHitPosition;
    float distance;
    int isHitVertical;
    int isFacingUp;
    int isFacingRight;
    int isFacingDown;
    int isFacingLeft;
    int WallType;
} rays[NUM_RAYS];


void CastAllRays();
void CastRay(float rayAngle, int stripId);
float NormalizeAngle(float angle);
float DistanceBetweenPoints(float x1, float y1, float x2, float y2);
