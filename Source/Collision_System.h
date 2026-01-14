#pragma once
#include "game.h"
#include <vector>
#include "Collision_Context.h"

struct CollisionSystem
{
    static bool CheckCollisionCircleLine(Vector2 circlePos, float radius, Vector2 lineStart, Vector2 lineEnd) noexcept;

    static void HandleProjectileCollisions(CollisionContext& ctx);
};