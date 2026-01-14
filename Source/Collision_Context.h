#pragma once
#include <vector>
#include "game.h"

struct CollisionContext
{
    Player& player;
    std::vector<Alien>& aliens;
    std::vector<Wall>& walls;
    std::vector<Projectile>& projectiles;
    int& score;
};