#include "assetsContainer.hpp"

void AssetsContainer::load()
{
    unknownTexture = LoadTexture("unknown.png");
    spike = LoadTexture("spike.png");
    szczupakf = LoadTexture("szczupak_final.png");
    spikeMask= LoadObstacleMask(LoadImage48("col_long.png"));

    backgroundSprite["kugelfisch3"] = LoadTexture("background/kugelfisch3.png");
    backgroundSprite["seahorse_import2"] = LoadTexture("background/seahorse_import2.png");
    backgroundSprite["SeaStar_2"] = LoadTexture("background/SeaStar_2.png");
    backgroundSprite["Medusa_Resized_2"] = LoadTexture("background/Medusa_Resized_2.png");
    obstaclesTexturesPlus.push_back(Load2DPlus("buton_off_full.png","buton_off_full_mask.png"));
    obstaclesTexturesPlus.push_back(Load2DPlus("szczupak_final.png","szczupak_final_mask.png"));
    obstaclesTexturesPlus.push_back(Load2DPlus("stranght3.png","stranght3_mask.png"));


    backgroundSprite["kugelfisch_Resized_1"] = LoadTexture("background/kugelfisch_Resized_1.png");
    backgroundSprite["Male_Konnik1"] = LoadTexture("background/Male_Konnik1.png");
    backgroundSprite["Medusa"] = LoadTexture("background/Medusa.png");
    backgroundSprite["darkBlue"] = LoadTexture("background/Zwykle_Tlo_darkBlue1.png");
    backgroundSprite[""] = LoadTexture("unknown.png");
}