#pragma once
#include <vector>
#include "raylib.h"

struct Star
{
    Vector2 initPosition{};
    Vector2 position{};
    float size{};
    Color color{};

    void Update(float offset) noexcept
    {
        position.x = initPosition.x + offset;
        position.y = initPosition.y;
    }

    void Render() const noexcept
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
            star.initPosition.x = static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150));
            star.initPosition.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
            star.color = SKYBLUE;
            star.size = GetRandomValue(1, 4) / 2.0f;

            star.position = star.initPosition;
            stars.push_back(star);
        }
    }

    static void Update(std::vector<Star>& stars, float offset) noexcept
    {
        for (auto& star : stars)
        {
            star.Update(offset);
        }
    }

    static void Render(const std::vector<Star>& stars) noexcept
    {
        for (const auto& star : stars)
        {
            star.Render();
        }
    }
};