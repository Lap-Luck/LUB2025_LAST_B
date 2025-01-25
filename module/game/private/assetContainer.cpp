#include "assetsContainer.hpp"

void AssetsContainer::load()
{
    unknownTexture = LoadTexture("unknown.png");
    spike = LoadTexture("spike.png");
    szczupakf = LoadTexture("szczupak_final.png");
    spikeMask= LoadObstacleMask(LoadImage48("col_long.png"));

    backgroundSprite["kugelfisch_Resized_1"] = LoadTexture("background/kugelfisch_Resized_1.png");
    backgroundSprite["Male_Konnik1"] = LoadTexture("background/Male_Konnik1.png");
    backgroundSprite["Medusa"] = LoadTexture("background/Medusa.png");
    backgroundSprite["darkBlue"] = LoadTexture("background/Zwykle_Tlo_darkBlue1.png");
    backgroundSprite[""] = LoadTexture("unknown.png");
}