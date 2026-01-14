#pragma once
#include "game.h"

struct WallSystem
{
    static void Update(std::vector<Wall>& walls)
    {
        for (auto& wall : walls)
        {
            if (wall.health < 1) wall.active = false;
        }

        // Optional: Remove inactive walls
        std::erase_if(walls, [](const Wall& w) { return !w.active; });
    }

    static void Render(const std::vector<Wall>& walls, const Resources& resources) noexcept
    {
        for (const auto& wall : walls)
        {
            DrawTexturePro(
                resources.barrierTexture.get(),
                { 0, 0, 704, 704 },
                { wall.position.x, wall.position.y, 200, 200 },
                { 100, 100 },
                0,
                WHITE
            );

            DrawText(TextFormat("%i", wall.health), static_cast<int>(wall.position.x) - 21, static_cast<int>(wall.position.y) + 10, 40, RED);
        }
    }
};
