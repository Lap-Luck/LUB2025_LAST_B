#include "assetsContainer.hpp"

void AssetsContainer::load()
{
    unknownTexture = LoadTexture("unknown.png");
    spike = LoadTexture("spike.png");
    szczupakf = LoadTexture("szczupak_final.png");
    spikeMask= LoadObstacleMask(LoadImage48("col_long.png"));

    backgroundSprite["darkBlue"] = LoadTexture("background/Zwykle_Tlo_darkBlue1.png");
    backgroundSprite[""] = LoadTexture("unknown.png");
}