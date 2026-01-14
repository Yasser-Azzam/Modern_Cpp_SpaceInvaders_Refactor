#pragma once
#include "game.h"
#include "raylib.h"
#include <string>

struct InputSystem
{
    static void HandleGameInput(Game& game)
    {
        switch (game.gameState)
        {
        case State::GAMEPLAY:
            // Player shooting
            if (IsKeyPressed(KEY_SPACE))
                game.SpawnPlayerProjectile();

            // Quit
            if (IsKeyReleased(KEY_Q))
                game.End();
            break;

        case State::STARTSCREEN:
            if (IsKeyReleased(KEY_SPACE))
                game.Reset(State::GAMEPLAY);
            break;

        case State::ENDSCREEN:
            HandleEndScreenInput(game);
            break;
        }
    }

private:
    static void HandleEndScreenInput(Game& game)
    {
        if (!game.newHighScore)
        {
            if (IsKeyReleased(KEY_ENTER))
                game.Continue();
            return;
        }

        game.mouseOnText =
            CheckCollisionPointRec(GetMousePosition(), game.textBox);

        SetMouseCursor(game.mouseOnText
            ? MOUSE_CURSOR_IBEAM
            : MOUSE_CURSOR_DEFAULT);

        if (game.mouseOnText)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= 32 && key <= 125 &&
                    game.playerName.size() < game.config.maxPlayerNameLength)
                {
                    game.playerName.push_back(static_cast<char>(key));
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !game.playerName.empty())
            {
                game.playerName.pop_back();
            }

            game.framesCounter++;
        }
        else
        {
            game.framesCounter = 0;
        }

        if (!game.playerName.empty() &&
            game.playerName.size() <= game.config.maxPlayerNameLength &&
            IsKeyReleased(KEY_ENTER))
        {
            game.InsertNewHighScore(game.playerName);
            game.newHighScore = false;
        }
    }
};