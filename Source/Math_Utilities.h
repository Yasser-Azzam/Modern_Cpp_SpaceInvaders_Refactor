#pragma once
#include "raylib.h"
#include <cmath>

namespace MathUtilities
{
    inline float Distance(Vector2 a, Vector2 b)
    {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return sqrtf(dx * dx + dy * dy);
    }

    inline float DistanceSquared(Vector2 a, Vector2 b)
    {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return dx * dx + dy * dy;
    }

    inline bool PointInCircle(Vector2 circleCenter, float radius, Vector2 point)
    {
        return DistanceSquared(circleCenter, point) < radius * radius;
    }
}