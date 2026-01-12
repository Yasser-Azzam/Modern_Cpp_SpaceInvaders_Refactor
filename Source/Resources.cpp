#include "Resources.h"
#include <iostream>;


Resources::Resources()   : alienTexture("./Assets/Alien.png"), barrierTexture("./Assets/Barrier.png"), laserTexture("./Assets/Laser.png")
{
    shipTextures.emplace_back("./Assets/Ship1.png");
    shipTextures.emplace_back("./Assets/Ship2.png");
    shipTextures.emplace_back("./Assets/Ship3.png");
}
