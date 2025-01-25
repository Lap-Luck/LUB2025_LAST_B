#include "assetsContainer.hpp"

void AssetsContainer::load()
{
    unknownTexture = LoadTexture("unknown.png");
    spike = LoadTexture("spike.png");
    szczupakf = LoadTexture("szczupak_final.png");
    spikeMask= LoadObstacleMask(LoadImage48("col_long.png"));

    obstaclesTexturesPlus.push_back(Load2DPlus("buton_off_full.png","buton_off_full_mask.png"));
    obstaclesTexturesPlus.push_back(Load2DPlus("szczupak_final.png","szczupak_final_mask.png"));
    obstaclesTexturesPlus.push_back(Load2DPlus("stranght3.png","stranght3_mask.png"));
    obstaclesTexturesPlus.push_back(Load2DPlus("hook.png","hook_mask.png"));


    backgroundSprite["kugelfisch3"] = LoadTexture("background/kugelfisch3.png");
    backgroundSprite["seahorse_import2"] = LoadTexture("background/seahorse_import2.png");
    backgroundSprite["SeaStar_2"] = LoadTexture("background/SeaStar_2.png");
    backgroundSprite["Medusa_Resized_2"] = LoadTexture("background/Medusa_Resized_2.png");
    backgroundSprite["hook"] = LoadTexture("background/hook.png");
    backgroundSprite["darkBlue"] = LoadTexture("background/Zwykle_Tlo_darkBlue1.png");
    backgroundSprite["unknown"] = LoadTexture("unknown.png");
}