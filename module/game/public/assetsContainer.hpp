#pragma once
#include "obstacle.hpp"
#include "raylib.h"

class AssetsContainer
{
public:
    Texture2D unknownTexture {};
    Texture2D spike {};

    ObstacleMask spikeMask {};

    void load();

};
