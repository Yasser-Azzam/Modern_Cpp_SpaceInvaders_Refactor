#include "Resources.h"
#include <iostream>;


// Initialize everything using member initializer list
Resources::Resources()   : shipTextures{ TextureWrapper("./Assets/Ship1.png"), TextureWrapper("./Assets/Ship2.png"),  TextureWrapper("./Assets/Ship3.png") },
                           alienTexture("./Assets/Alien.png"), barrierTexture("./Assets/Barrier.png"), laserTexture("./Assets/Laser.png")
{

}