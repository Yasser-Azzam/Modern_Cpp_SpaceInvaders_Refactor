#pragma once
#include <cstddef>
#include "raylib.h"

struct GameConfig
{
    std::size_t starCount = 600;

    int maxPlayerNameLength = 8;

    int enemyShootCooldownFrames = 60;

    int alienFormationWidth = 8;
    int alienFormationHeight = 5;
    int alienSpacing = 80;

    float backgroundScrollDivisor = 15.0f;

    float playerWidth = 100.0f;
    float playerHeight = 100.0f;
    Vector2 playerOrigin = { 50.0f, 50.0f };

    float alienWidth = 100.0f;
    float alienHeight = 100.0f;
    Vector2 alienOrigin = { 50.0f, 50.0f };

    float wallWidth = 200.0f;
    float wallHeight = 200.0f;
    Vector2 wallOrigin = { 100.0f, 100.0f };
    int wallHealthTextOffsetX = -21;
    int wallHealthTextOffsetY = 10;
    int wallHealthFontSize = 40;
    Color wallHealthColor = RED;

    float projectileWidth = 50.0f;
    float projectileHeight = 50.0f;
    Vector2 projectileOrigin = { 25.0f, 25.0f };

    int hudScoreX = 50;
    int hudScoreY = 20;
    int hudLivesX = 50;
    int hudLivesY = 70;
    int hudFontSize = 40;
    Color hudColor = YELLOW;

    int highscoreTitleX = 600;
    int highscoreTitleY = 300;
    int highscoreBoxX = 600;
    int highscoreBoxY = 500;
    int highscoreBoxWidth = 225;
    int highscoreBoxHeight = 50;
    int highscoreFontSize = 40;
    Color highscoreTextColor = MAROON;
    Color highscoreBoxColor = LIGHTGRAY;
    Color highscoreBoxBorderInactive = DARKGRAY;
    Color highscoreBoxBorderActive = RED;
    int highscoreTextOffsetX = 5;
    int highscoreTextOffsetY = 8;

    int leaderboardTitleX = 50;
    int leaderboardTitleY = 100;
    int leaderboardStartY = 140;
    int leaderboardRowSpacing = 40;
    int leaderboardFontSize = 40;
    Color leaderboardColor = YELLOW;

    int startScreenTitleX = 200;
    int startScreenTitleY = 100;
    int startScreenPromptX = 200;
    int startScreenPromptY = 350;
    int startScreenFontSizeLarge = 160;
    int startScreenFontSizeSmall = 40;
    Color startScreenColor = YELLOW;

    Color defaultWhite = WHITE;
};