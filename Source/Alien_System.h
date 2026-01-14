#pragma once
#include "game.h"
#include "raylib.h"

struct AlienSystem
{
    static void Update(std::vector<Alien>& aliens)
    {
        int window_width = GetScreenWidth();
        for (auto& alien : aliens)
        {
            if (alien.moveRight)
            {
                alien.position.x += alien.speed;
                if (alien.position.x >= window_width)
                {
                    alien.moveRight = false;
                    alien.position.y += 50;
                }
            }
            else
            {
                alien.position.x -= alien.speed;
                if (alien.position.x <= 0)
                {
                    alien.moveRight = true;
                    alien.position.y += 50;
                }
            }
        }
    }

    static void Render(const std::vector<Alien>& aliens, const Resources& resources)
    {
        for (const auto& alien : aliens)
        {
            DrawTexturePro(
                resources.alienTexture.get(),
                { 0, 0, 352, 352 },
                { alien.position.x, alien.position.y, 100, 100 },
                { 50, 50 },
                0,
                WHITE
            );
        }
    }
};