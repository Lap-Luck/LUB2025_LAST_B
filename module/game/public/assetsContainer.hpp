#pragma once
#include <map>
#include <string>

#include "obstacle.hpp"
#include "raylib.h"

struct Texture2DPlus {
    Texture2D img;
    std::vector<ObstacleMask> masks;
    float obstaclePixelsSizeX;
    float obstaclePixelsSizeY;
};

namespace {
    Texture2DPlus Load2DPlus(char* path) {
        Texture2DPlus texture_2d_plus;
        texture_2d_plus.img = LoadTexture(path);

        ObstacleMask spikeMask;
        spikeMask= LoadObstacleMask(LoadImage48(path));
        texture_2d_plus.masks.push_back(std::move(spikeMask));
    }

    Texture2DPlus Load2DPlus(char* path,char* path2) {
        Texture2DPlus texture_2d_plus;
        texture_2d_plus.img = LoadTexture(path);

        ObstacleMask spikeMask;
        spikeMask= LoadObstacleMask(LoadImage48(path2));
        texture_2d_plus.masks.push_back(std::move(spikeMask));

        texture_2d_plus.obstaclePixelsSizeX=texture_2d_plus.img.width/((float)spikeMask.size.x);
        texture_2d_plus.obstaclePixelsSizeY=texture_2d_plus.img.height/((float)spikeMask.size.y);


        return  texture_2d_plus;
    }


}

class AssetsContainer
{
public:
    Texture2D unknownTexture {};
    Texture2D spike {};
    Texture2D szczupakf{};

    ObstacleMask spikeMask {};

    std::map<std::string,Texture2D> backgroundSprite {};

    std::vector<Texture2DPlus> obstaclesTexturesPlus{};


    void load();

};
