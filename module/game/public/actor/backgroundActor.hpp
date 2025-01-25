#pragma once
#include "actor.hpp"
#include "gameState.hpp"
#include "vec2.hpp"



class BackgroundActor : public Actor
{
public:
    std::string selectedTexture = "";

    BackgroundActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~BackgroundActor()
    {
    }

    void onPlaced() override
    {

    }

    void onSerialize(ISerialize* inSerialize) override
    {
        Actor::onSerialize(inSerialize);

        std::vector<std::string> keys;
        for (auto& it : state.assets.backgroundSprite)
        {
            keys.push_back(it.first);
        }

        inSerialize->propertyEnum("selectedTexture",keys,selectedTexture);
    }

    void onDraw() override
    {
        auto& texture = state.assets.backgroundSprite[selectedTexture];
        DrawTexture(texture,pos.x,pos.y,WHITE);
    }
};
