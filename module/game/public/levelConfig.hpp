#pragma once

#include "serialize.hpp"

class LevelConfig
{
public:
    bool spawnBubble {true};
    int  levelHeight {1};

    void onSerialize(ISerialize* inSerialize)
    {
        inSerialize->propertyBool("spawnBubble",spawnBubble);
        inSerialize->propertyInt("levelHeight",levelHeight);

    };
};