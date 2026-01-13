#pragma once
#include <array>
#include "RAII_Texture_Wrapper.h"

struct Resources {
    std::array<TextureWrapper, 3> shipTextures;
    TextureWrapper alienTexture;
    TextureWrapper barrierTexture;
    TextureWrapper laserTexture;

    Resources();
};