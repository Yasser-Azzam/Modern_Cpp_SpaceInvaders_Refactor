#pragma once
#include "game.h"
#include "raylib.h"
#include <string>

struct UISystem
{
    static void RenderHUD(const Game& game)
    {
        DrawText(TextFormat("Score: %i", game.score), 50, 20, 40, YELLOW);
        DrawText(TextFormat("Lives: %i", game.player.lives), 50, 70, 40, YELLOW);
    }

    static void RenderHighScoreEntry(const Game& game)
    {
        DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
        DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

        DrawRectangleRec(game.textBox, LIGHTGRAY);

        if (game.mouseOnText)
            DrawRectangleLines((int)game.textBox.x, (int)game.textBox.y, (int)game.textBox.width, (int)game.textBox.height, RED);
        else
            DrawRectangleLines((int)game.textBox.x, (int)game.textBox.y, (int)game.textBox.width, (int)game.textBox.height, DARKGRAY);

        DrawText(game.playerName.c_str(), (int)game.textBox.x + 5, (int)game.textBox.y + 8, 40, MAROON);
        DrawText(TextFormat("INPUT CHARS: %i/%i", game.playerName.size(), 8), 600, 600, 20, YELLOW);

        if (game.mouseOnText && game.playerName.size() < 9 && ((game.framesCounter / 20) % 2) == 0)
        {
            DrawText("_", (int)game.textBox.x + 8 + MeasureText(game.playerName.c_str(), 40), (int)game.textBox.y + 12, 40, MAROON);
        }

        if (game.playerName.size() > 0 && game.playerName.size() < 9)
        {
            DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
        }
        else if (game.playerName.size() >= 9)
        {
            DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
        }
    }

    static void RenderLeaderboard(const Game& game)
    {
        DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
        DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

        for (int i = 0; i < game.Leaderboard.size(); i++)
        {
            DrawText(game.Leaderboard[i].name.c_str(), 50, 140 + (i * 40), 40, YELLOW);
            DrawText(TextFormat("%i", game.Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
        }
    }
};