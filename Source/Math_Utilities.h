#pragma once
#include "raylib.h"
#include <cmath>

namespace MathUtilities
{
    inline float Distance(Vector2 a, Vector2 b) noexcept
    {
        const float dx = b.x - a.x;
        const float dy = b.y - a.y;
        return sqrtf(dx * dx + dy * dy);
    }

    inline constexpr float DistanceSquared(Vector2 a, Vector2 b)
    {
        const float dx = b.x - a.x;
        const float dy = b.y - a.y;
        return dx * dx + dy * dy;
    }

    inline bool constexpr PointInCircle(Vector2 circleCenter, float radius, Vector2 point)
    {
        return DistanceSquared(circleCenter, point) < radius * radius;
    }
}