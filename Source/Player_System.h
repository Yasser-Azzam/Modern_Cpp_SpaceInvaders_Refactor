#pragma once
#include "game.h"
#include "raylib.h"

struct PlayerSystem
{
    static void Update(Player& player) noexcept
    {
        // Movement
        int direction = 0;
        if (IsKeyDown(KEY_LEFT)) direction--;
        if (IsKeyDown(KEY_RIGHT)) direction++;

        player.x_pos += player.speed * direction;

        const float screenWidth = static_cast<float>(GetScreenWidth());

        if (player.x_pos < player.radius)
            player.x_pos = player.radius;
        else if (player.x_pos > screenWidth - player.radius)
            player.x_pos = screenWidth - player.radius;

        player.timer += GetFrameTime();
        if (player.timer > 0.4f)
        {
            player.activeTexture = (player.activeTexture + 1) % 3;
            player.timer = 0;
        }
    }

    static void Render(const Player& player, const Resources& resources) noexcept
    {
        const float window_height = static_cast<float>(GetScreenHeight());
        const size_t idx = static_cast<size_t>(player.activeTexture % resources.shipTextures.size());
        
        DrawTexturePro(
            resources.shipTextures[idx].get(),
            { 0, 0, 352, 352 },
            { player.x_pos, window_height - player.player_base_height, 100, 100 },
            { 50, 50 },
            0,
            WHITE
        );
    }
};