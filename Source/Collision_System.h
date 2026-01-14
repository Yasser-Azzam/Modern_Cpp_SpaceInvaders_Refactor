#pragma once
#include "game.h"
#include <vector>

struct CollisionSystem
{
    static bool CheckCollisionCircleLine(Vector2 circlePos, float radius, Vector2 lineStart, Vector2 lineEnd);

    static void HandleProjectileCollisions(Game& game);
};