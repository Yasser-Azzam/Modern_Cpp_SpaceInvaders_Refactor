#pragma once
#include "game.h"
#include "raylib.h"

struct PlayerSystem
{
    static void Update(Player& player)
    {
        // Movement
        int direction = 0;
        if (IsKeyDown(KEY_LEFT)) direction--;
        if (IsKeyDown(KEY_RIGHT)) direction++;

        player.x_pos += player.speed * direction;

        if (player.x_pos < player.radius)
            player.x_pos = player.radius;
        else if (player.x_pos > GetScreenWidth() - player.radius)
            player.x_pos = GetScreenWidth() - player.radius;

        // Animation frame
        player.timer += GetFrameTime();
        if (player.timer > 0.4f)
        {
            player.activeTexture = (player.activeTexture + 1) % 3;
            player.timer = 0;
        }
    }

    static void Render(const Player& player, const Resources& resources)
    {
        float window_height = GetScreenHeight();
        DrawTexturePro(
            resources.shipTextures[player.activeTexture].get(),
            { 0, 0, 352, 352 },
            { player.x_pos, window_height - player.player_base_height, 100, 100 },
            { 50, 50 },
            0,
            WHITE
        );
    }
};