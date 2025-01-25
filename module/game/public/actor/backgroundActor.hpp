#pragma once
#include "actor.hpp"
#include "gameState.hpp"
#include "vec2.hpp"



class BackgroundActor : public Actor
{
public:
    ACTOR_BODY(BackgroundActor);

    std::string selectedTexture = "unknown";
    float scale = 1.0;
    float rotation = 0.0;

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
        inSerialize->propertyFloat("scale",scale);
        inSerialize->propertyFloat("rotation",rotation);
    }

    void onDraw() override
    {
        auto& texture = state.assets.backgroundSprite[selectedTexture];
        DrawTextureEx(texture,pos,rotation,scale,WHITE);
    }
};
