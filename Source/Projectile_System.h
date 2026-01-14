#pragma once
#include "game.h"
#include "GameConfig.h"

struct ProjectileSystem
{
    static void Update(std::vector<Projectile>& projectiles) noexcept
    {
        for (auto& proj : projectiles)
        {
            proj.position.y -= proj.speed;

            proj.lineStart.x = proj.position.x;
            proj.lineEnd.x = proj.position.x;
            proj.lineStart.y = proj.position.y - 15;
            proj.lineEnd.y = proj.position.y + 15;
        }
    }

    static void Render(const std::vector<Projectile>& projectiles, const Resources& resources, const GameConfig& cfg) noexcept
    {
        for (const auto& proj : projectiles)
        {
            DrawTexturePro(
                resources.laserTexture.get(),
                { 0, 0, 176, 176 },
                { proj.position.x, proj.position.y, cfg.projectileWidth, cfg.projectileHeight },
                cfg.projectileOrigin,
                0,
                cfg.defaultWhite
            );
        }
    }
};