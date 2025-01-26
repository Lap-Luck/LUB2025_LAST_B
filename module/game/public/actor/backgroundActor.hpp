#pragma once
#include "actor.hpp"
#include "gameState.hpp"
#include "vec2.hpp"



class BackgroundActor : public Actor, public IActorModifyParam
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
        DrawTexturePro(
            texture,
            {0,0,(float)texture.width,(float)texture.height},
            {pos.x,pos.y,texture.width*scale,texture.height*scale},
            Vector2{texture.width*scale/2.f,texture.height*scale/2.f},
            rotation,
            WHITE
        );
    }

    void requestChangeScale(float inChange) override
    {
        scale += inChange;
    }
    void requestChangeRotation(float inChange) override
    {
        rotation += inChange;
    }
};
