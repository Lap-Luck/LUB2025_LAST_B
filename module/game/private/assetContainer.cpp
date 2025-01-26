#include <cassert>
#include <iostream>
#include <ostream>

#include "assetsContainer.hpp"

void AssetsContainer::load()
{
    unknownTexture = LoadTexture("unknown.png");
    spike = LoadTexture("spike.png");
    szczupakf = LoadTexture("szczupak_final.png");
    spikeMask= LoadObstacleMask(LoadImage48("col_long.png"));

    //obstaclesTexturesPlus.push_back(Load2DPlus("buton_off_full.png","buton_off_full_mask.png"));
    //obstaclesTexturesPlus.push_back(Load2DPlus("szczupak_final.png","szczupak_final_mask.png"));
    //obstaclesTexturesPlus.push_back(Load2DPlus("stranght3.png","stranght3_mask.png"));
    //obstaclesTexturesPlus.push_back(Load2DPlus("hook.png","hook_mask.png"));
    int i=0;
    TraceLog(LOG_INFO,"obstacles");
    while (true) {
        bool ex=DirectoryExists(TextFormat("obstacles/%d",i));
        if (!ex) {
            break;
        }
        {
            auto df=LoadDirectoryFiles(TextFormat("obstacles/%d",i));
            if (df.capacity==2) {
                obstaclesTexturesPlus.push_back(Load2DPlus(df.paths[0],df.paths[1]));
                obstaclesTexturesPlusR.push_back(Load2DPlus(df.paths[0],df.paths[1],true));
            }
            else {
                assert(false);
            }
            for (int i:range(df.capacity)) {
                auto path=df.paths[i];
                TraceLog(LOG_INFO,path);
            }
        }
        TraceLog(LOG_INFO,TextFormat("obstacles/%d",i));
        i++;
    }

    auto backgrounds = LoadDirectoryFiles("background\\");
    for (int idx = 0; idx != backgrounds.count; idx++)
    {
        std::string path= backgrounds.paths[idx];
        auto s = path.find_last_of('\\');
        auto e = path.find_last_of('.');

        backgroundSprite[path.substr(s+1,e-s-1)] = LoadTexture(path.c_str());
    }
}