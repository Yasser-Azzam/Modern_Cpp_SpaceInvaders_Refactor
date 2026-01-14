#pragma once
#include "game.h"

struct ProjectileSystem
{
    static void Update(std::vector<Projectile>& projectiles)
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

    static void Render(const std::vector<Projectile>& projectiles, const Resources& resources)
    {
        for (const auto& proj : projectiles)
        {
            DrawTexturePro(
                resources.laserTexture.get(),
                { 0, 0, 176, 176 },
                { proj.position.x, proj.position.y, 50, 50 },
                { 25, 25 },
                0,
                WHITE
            );
        }
    }
};