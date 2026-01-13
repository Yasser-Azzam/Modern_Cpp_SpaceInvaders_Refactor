#pragma once
#include <raylib.h>
#include <utility>
#include <stdexcept>


class TextureWrapper {
public:
    TextureWrapper() = default;

    explicit TextureWrapper(const char* path) : texture_(LoadTexture(path))
    {
        if (texture_.id == 0) 
        {
            throw std::runtime_error("Failed to load texture");
        }
    }

    ~TextureWrapper() {
        if (texture_.id != 0) 
        {
            UnloadTexture(texture_);
        }
    }

    TextureWrapper(const TextureWrapper&) = delete;
    TextureWrapper& operator=(const TextureWrapper&) = delete;

    TextureWrapper(TextureWrapper&& other) noexcept  : texture_(std::exchange(other.texture_, {})) 
    {

    }

    TextureWrapper& operator=(TextureWrapper&& other) noexcept 
    {
        if (this != &other) 
        {
            if (texture_.id != 0) 
            {
                UnloadTexture(texture_);
            }

            texture_ = std::exchange(other.texture_, {});
        }

        return *this;
    }

    [[nodiscard]] const Texture2D& get() const noexcept 
    {
        return texture_;
    }

private:
    Texture2D texture_{};
};