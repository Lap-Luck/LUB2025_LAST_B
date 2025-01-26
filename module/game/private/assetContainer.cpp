#include <cassert>
#include <iostream>
#include <ostream>

#include "assetsContainer.hpp"

void loadFromFolder(std::map<std::string,Texture2D>& ref,std::string name)
{
    auto backgrounds = LoadDirectoryFiles((name+"\\").c_str());
    for (int idx = 0; idx != backgrounds.count; idx++)
    {
        std::string path= backgrounds.paths[idx];
        auto s = path.find_last_of('\\');
        auto e = path.find_last_of('.');

        ref[path.substr(s+1,e-s-1)] = LoadTexture(path.c_str());
    }
}

std::vector<std::string> getAllLevels()
{
    std::vector<std::string> out;
    auto backgrounds = LoadDirectoryFiles(("levels\\"));
    for (int idx = 0; idx != backgrounds.count; idx++)
    {
        std::string path= backgrounds.paths[idx];
        auto s = path.find_last_of('\\');
        auto e = path.find_last_of('.');

        out.push_back(path.substr(s+1,e-s-1));
    }
    return out;
}

void AssetsContainer::load()
{
    allLevelsName = getAllLevels();

    unknownTexture = LoadTexture("unknown.png");
    spike = LoadTexture("spike.png");
    szczupakf = LoadTexture("szczupak_final.png");
    {
        Image i=LoadImage("szczupak_final.png");
        ImageFlipHorizontal(&i);
        szczupakfR =LoadTextureFromImage(i);

    }

    doort=LoadTexture("door.png");
    dooro=LoadObstacleMask(LoadImage48("door_coli.png"));

    spikeMask= LoadObstacleMask(LoadImage48("col_long.png"));

    {
        auto cmasks=LoadObstacleMasks(LoadImage48("szczupak_final_mask.png"),2);

        fish1=cmasks[0];
        fish2=cmasks[1];
    }
    {
        auto cmasks=LoadObstacleMasks(LoadImage48("szczupak_final_mask.png",true),2);

        fish1R=cmasks[0];
        fish2R=cmasks[1];
    }


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

    loadFromFolder(backgroundSprite,"background");
    loadFromFolder(buttonSprite,"button");

}