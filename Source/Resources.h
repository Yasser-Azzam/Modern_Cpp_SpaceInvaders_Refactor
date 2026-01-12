#pragma once
#include "vector"
#include "RAII_Texture_Wrapper.h"

struct Resources {
    Resources();

    std::vector<TextureWrapper> shipTextures;
    TextureWrapper alienTexture;
    TextureWrapper barrierTexture;
    TextureWrapper laserTexture;
};