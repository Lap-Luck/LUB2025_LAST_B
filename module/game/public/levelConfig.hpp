#pragma once

#include "serialize.hpp"

class LevelConfig
{
public:
    bool spawnBubble {true};

    void onSerialize(ISerialize* inSerialize)
    {
        inSerialize->propertyBool("spawnBubble",spawnBubble);

    };
};