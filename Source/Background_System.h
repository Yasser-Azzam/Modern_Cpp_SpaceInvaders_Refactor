#pragma once
#include <vector>
#include "raylib.h"

struct Star
{
    Vector2 initPosition{};
    Vector2 position{};
    float size{};
    Color color{};

    void Update(float offset)
    {
        position.x = initPosition.x + offset;
        position.y = initPosition.y;
    }

    void Render() const
    {
        DrawCircle(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            size,
            color
        );
    }
};

struct BackgroundSystem
{
    static void Initialize(std::vector<Star>& stars, std::size_t starCount)
    {
        stars.clear();
        stars.reserve(starCount);

        for (std::size_t i = 0; i < starCount; ++i)
        {
            Star star;
            star.initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
            star.initPosition.y = GetRandomValue(0, GetScreenHeight());
            star.color = SKYBLUE;
            star.size = GetRandomValue(1, 4) / 2.0f;

            star.position = star.initPosition;
            stars.push_back(star);
        }
    }

    static void Update(std::vector<Star>& stars, float offset)
    {
        for (auto& star : stars)
        {
            star.Update(offset);
        }
    }

    static void Render(const std::vector<Star>& stars)
    {
        for (const auto& star : stars)
        {
            star.Render();
        }
    }
};