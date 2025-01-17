#include "data/ray.h"

#include <float.h>
#include <tgmath.h>

#include "grid.h"
#include "player.h"


struct RayCast rays[NUM_RAYS];

void CastAllRays() {
    auto rayAngle = (float) player.rotation - FOV / 2;
    for (auto stripId = 0; stripId < NUM_RAYS; stripId++) {
        CastRay(rayAngle, stripId);
        rayAngle += FOV / NUM_RAYS;
    }
}

void CastRay(float rayAngle, const int stripId) {
    rayAngle = NormalizeAngle(rayAngle);
    const auto isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    const auto isRayFacingUp = !isRayFacingDown;

    const auto isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    const auto isRayFacingLeft = !isRayFacingRight;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    auto foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    auto horzWallContent = 0;

    float yIntercept = floor(player.position.y / TILE_SIZE) * TILE_SIZE;
    yIntercept += isRayFacingDown ? TILE_SIZE : 0;

    float xIntercept = player.position.x + (yIntercept - player.position.y) / tan(rayAngle);

    float yStep = TILE_SIZE;
    yStep *= isRayFacingUp ? -1 : 1;

    float xStep = TILE_SIZE / tan(rayAngle);
    xStep *= (isRayFacingLeft && xStep > 0) ? -1 : 1;
    xStep *= (isRayFacingRight && xStep < 0) ? -1 : 1;

    auto nextHorzTouchX = xIntercept;
    auto nextHorzTouchY = yIntercept;

    while (nextHorzTouchX >= 0 &&
           nextHorzTouchX <= GRID_COL_COUNT * TILE_SIZE &&
           nextHorzTouchY >= 0 &&
           nextHorzTouchY <= GRID_ROW_COUNT * TILE_SIZE) {
        const auto xToCheck = nextHorzTouchX;
        const auto yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if (HasWallAtGridPosition(xToCheck, yToCheck)) {
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = grid[(int) floor(yToCheck / TILE_SIZE)][(int) floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = true;
            break;
        }
        nextHorzTouchX += xStep;
        nextHorzTouchY += yStep;
    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    auto foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    auto vertWallContent = 0;

    xIntercept = floor(player.position.x / TILE_SIZE) * TILE_SIZE;
    xIntercept += isRayFacingRight ? TILE_SIZE : 0;

    yIntercept = player.position.y + (xIntercept - player.position.x) * tan(rayAngle);

    xStep = TILE_SIZE;
    xStep *= isRayFacingLeft ? -1 : 1;

    yStep = TILE_SIZE * tan(rayAngle);
    yStep *= isRayFacingUp && yStep > 0 ? -1 : 1;
    yStep *= isRayFacingDown && yStep < 0 ? -1 : 1;

    auto nextVertTouchX = xIntercept;
    auto nextVertTouchY = yIntercept;

    while (nextVertTouchX >= 0 &&
           nextVertTouchX <= GRID_COL_COUNT * TILE_SIZE &&
           nextVertTouchY >= 0 &&
           nextVertTouchY <= GRID_ROW_COUNT * TILE_SIZE) {
        const auto xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        const auto yToCheck = nextVertTouchY;

        if (HasWallAtGridPosition(xToCheck, yToCheck)) {
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = grid[(int) floor(yToCheck / TILE_SIZE)][(int) floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = true;
            break;
        }
        nextVertTouchX += xStep;
        nextVertTouchY += yStep;
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    const auto horzHitDistance = foundHorzWallHit
                                ? DistanceBetweenPoints(player.position.x, player.position.y, horzWallHitX, horzWallHitY)
                                : FLT_MAX;
    const auto vertHitDistance = foundVertWallHit
                                ? DistanceBetweenPoints(player.position.x, player.position.y, vertWallHitX, vertWallHitY)
                                : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        rays[stripId].distance = vertHitDistance;
        rays[stripId].wallHitPosition.x = vertWallHitX;
        rays[stripId].wallHitPosition.y = vertWallHitY;
        rays[stripId].WallType = vertWallContent;
        rays[stripId].isHitVertical = true;
        rays[stripId].angle = rayAngle;
    } else {
        rays[stripId].distance = horzHitDistance;
        rays[stripId].wallHitPosition.x = horzWallHitX;
        rays[stripId].wallHitPosition.y = horzWallHitY;
        rays[stripId].WallType = horzWallContent;
        rays[stripId].isHitVertical = false;
        rays[stripId].angle = rayAngle;
    }
}

float NormalizeAngle(float angle) {
    angle = remainder(angle, TWO_PI);
    if (angle < 0) {
        angle = TWO_PI + angle;
    }
    return angle;
}

float DistanceBetweenPoints(const float x1, const float y1, const float x2, const float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
