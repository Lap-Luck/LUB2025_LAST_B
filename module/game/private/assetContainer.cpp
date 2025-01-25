#include "assetsContainer.hpp"

void AssetsContainer::load()
{
    unknownTexture = LoadTexture("unknown.png");
    spike = LoadTexture("spike.png");
    spikeMask.load(LoadImage48("col_long.png"));
}