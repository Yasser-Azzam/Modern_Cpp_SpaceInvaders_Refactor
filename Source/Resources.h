#pragma once
#include <array>
#include "RAII_Texture_Wrapper.h"

struct Resources {
    std::array<TextureWrapper, 3> shipTextures;
    TextureWrapper alienTexture;
    TextureWrapper barrierTexture;
    TextureWrapper laserTexture;

    Resources()
        : shipTextures{
            TextureWrapper("./Assets/Ship1.png"),
            TextureWrapper("./Assets/Ship2.png"),
            TextureWrapper("./Assets/Ship3.png")
        }
        , alienTexture("./Assets/Alien.png")
        , barrierTexture("./Assets/Barrier.png")
        , laserTexture("./Assets/Laser.png")
    {
    }
};