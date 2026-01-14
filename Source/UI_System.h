#pragma once
#include "game.h"
#include "raylib.h"
#include <string>
#include "GameConfig.h"


struct UISystem
{
    static void RenderHUD(const Game& game, const GameConfig& cfg) noexcept
    {
        DrawText(TextFormat("Score: %i", game.score), cfg.hudScoreX, cfg.hudScoreY, cfg.hudFontSize, cfg.hudColor);
        DrawText(TextFormat("Lives: %i", game.player.lives), cfg.hudLivesX, cfg.hudLivesY, cfg.hudFontSize, cfg.hudColor);
    }

    static void RenderHighScoreEntry(const Game& game, const GameConfig& cfg) noexcept
    {
        DrawText("NEW HIGHSCORE!", cfg.highscoreTitleX, cfg.highscoreTitleY, cfg.highscoreFontSize, cfg.hudColor);
        DrawText("PLACE MOUSE OVER INPUT BOX!", cfg.highscoreTitleX, cfg.highscoreTitleY + 100, cfg.hudFontSize / 2, cfg.hudColor);

        DrawRectangleRec(game.textBox, cfg.highscoreBoxColor);

        DrawRectangleLines(
            static_cast<int>(game.textBox.x),
            static_cast<int>(game.textBox.y),
            static_cast<int>(game.textBox.width),
            static_cast<int>(game.textBox.height),
            game.mouseOnText ? cfg.highscoreBoxBorderActive : cfg.highscoreBoxBorderInactive
        );

        DrawText(game.playerName.c_str(), static_cast<int>(game.textBox.x) + cfg.highscoreTextOffsetX, static_cast<int>(game.textBox.y) + cfg.highscoreTextOffsetY, cfg.highscoreFontSize, cfg.highscoreTextColor);

        if (game.mouseOnText && game.playerName.size() < 9 && ((game.framesCounter / 20) % 2) == 0)
        {
            DrawText("_", static_cast<int>(game.textBox.x) + cfg.highscoreTextOffsetX + MeasureText(game.playerName.c_str(), cfg.highscoreFontSize), static_cast<int>(game.textBox.y) + cfg.highscoreTextOffsetY + 4, cfg.highscoreFontSize, cfg.highscoreTextColor);
        }

        if (!game.playerName.empty() && game.playerName.size() < 9)
        {
            DrawText("PRESS ENTER TO CONTINUE", cfg.highscoreTitleX, cfg.highscoreTitleY + 500, cfg.hudFontSize, cfg.hudColor);
        }
        else if (game.playerName.size() >= 9)
        {
            DrawText("Press BACKSPACE to delete chars...", cfg.highscoreTitleX, cfg.highscoreTitleY + 150, cfg.hudFontSize / 2, cfg.hudColor);
        }
    }

    static void RenderLeaderboard(const Game& game, const GameConfig& cfg) noexcept
    {
        DrawText("PRESS ENTER TO CONTINUE", cfg.hudScoreX + 550, cfg.hudScoreY + 180, cfg.hudFontSize, cfg.hudColor);
        DrawText("LEADERBOARD", cfg.leaderboardTitleX, cfg.leaderboardTitleY, cfg.leaderboardFontSize, cfg.leaderboardColor);

        for (int i = 0; i < game.Leaderboard.size(); i++)
        {
            DrawText(game.Leaderboard[i].name.c_str(), cfg.leaderboardTitleX, cfg.leaderboardStartY + (i * cfg.leaderboardRowSpacing), cfg.leaderboardFontSize, cfg.leaderboardColor);
            DrawText(TextFormat("%i", game.Leaderboard[i].score), cfg.leaderboardTitleX + 300, cfg.leaderboardStartY + (i * cfg.leaderboardRowSpacing), cfg.leaderboardFontSize, cfg.leaderboardColor);
        }
    }

};