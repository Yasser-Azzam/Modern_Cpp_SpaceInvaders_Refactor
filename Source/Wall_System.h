#pragma once
#include "game.h"
#include "GameConfig.h"


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

    static void Render(const std::vector<Wall>& walls, const Resources& resources, const GameConfig& cfg) noexcept
    {
        for (const auto& wall : walls)
        {
            DrawTexturePro(
                resources.barrierTexture.get(),
                { 0, 0, 704, 704 },
                { wall.position.x, wall.position.y, cfg.wallWidth, cfg.wallHeight },
                cfg.wallOrigin,
                0,
                cfg.defaultWhite
            );

            DrawText(TextFormat("%i", wall.health), static_cast<int>(wall.position.x) + cfg.wallHealthTextOffsetX, 
                static_cast<int>(wall.position.y) + cfg.wallHealthTextOffsetY, cfg.wallHealthFontSize, cfg.wallHealthColor);
        }
    }
};
