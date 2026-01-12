#pragma once
#include <vector>


struct Resources {
    Resources();

    std::vector<TextureHandle> shipTextures;
    TextureHandle alienTexture;
    TextureHandle barrierTexture;
    TextureHandle laserTexture;
};