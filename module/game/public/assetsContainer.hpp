#pragma once
#include "obstacle.hpp"
#include "raylib.h"

struct Texture2DPlus {
    Texture2D img;
    std::vector<ObstacleMask> masks;
};

namespace {
    Texture2DPlus Load2DPlus(char* path) {
        Texture2DPlus texture_2d_plus;
        texture_2d_plus.img = LoadTexture(path);

        ObstacleMask spikeMask;
        spikeMask= LoadObstacleMask(LoadImage48(path));
        texture_2d_plus.masks.push_back(std::move(spikeMask));
    }


}

class AssetsContainer
{
public:
    Texture2D unknownTexture {};
    Texture2D spike {};
    Texture2D szczupakf{};

    ObstacleMask spikeMask {};

    void load();

};
