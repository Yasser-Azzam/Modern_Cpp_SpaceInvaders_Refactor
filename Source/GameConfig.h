#pragma once
#include <cstddef>

struct GameConfig
{
    std::size_t starCount = 600;

    int maxPlayerNameLength = 8;

    int enemyShootCooldownFrames = 60;

    int alienFormationWidth = 8;
    int alienFormationHeight = 5;
    int alienSpacing = 80;

    float backgroundScrollDivisor = 15.0f;
};