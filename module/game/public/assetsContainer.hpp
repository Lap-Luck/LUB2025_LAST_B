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

    Texture2DPlus Load2DPlus(char* path,char* path2,bool rev=false) {
        Texture2DPlus texture_2d_plus;
        auto im=LoadImage(path);
        if (rev) {
            ImageFlipHorizontal(&(im));
        }

        texture_2d_plus.img = LoadTextureFromImage(im);


        ObstacleMask spikeMask;
        spikeMask= LoadObstacleMask(LoadImage48(path2,rev));
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
    Texture2D szczupakfR{};

    ObstacleMask spikeMask {};

    ObstacleMask fish1{};
    ObstacleMask fish2{};
    ObstacleMask fish1R{};
    ObstacleMask fish2R{};

    std::map<std::string,Texture2D> backgroundSprite {};

    std::vector<Texture2DPlus> obstaclesTexturesPlus{};
    std::vector<Texture2DPlus> obstaclesTexturesPlusR{};

    Texture2D doort{};
    ObstacleMask dooro{};

    void load();

};
