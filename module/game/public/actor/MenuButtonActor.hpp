#pragma once
#include "actor.hpp"
#include "gameState.hpp"
#include "vec2.hpp"



class MenuButtonActor : public Actor, public IActorModifyParam
{
public:
    ACTOR_BODY(MenuButtonActor);

    std::string selectedTexture = "unknown";
    std::string loadLevelOnClick = "default";
    float scale = 1.0;

    MenuButtonActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~MenuButtonActor() override
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
        inSerialize->propertyString("loadLevelOnClick",loadLevelOnClick);
        inSerialize->propertyFloat("scale",scale);
    }

    void onUpdate() override
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            auto& texture = state.assets.backgroundSprite[selectedTexture];
            float offset = texture.width*scale/2.f;
            if(
                state.temp.mouseWorldPos.x > pos.x - offset &&
                state.temp.mouseWorldPos.x < pos.x + offset &&
                state.temp.mouseWorldPos.y > pos.y - offset &&
                state.temp.mouseWorldPos.y < pos.y + offset
            )
            {
                state.sceneControl.changeLevel = loadLevelOnClick;
            }
        }
    }

    void onDraw() override
    {
        auto& texture = state.assets.backgroundSprite[selectedTexture];
        DrawTexturePro(
            texture,
            {0,0,(float)texture.width,(float)texture.height},
            {pos.x,pos.y,texture.width*scale,texture.height*scale},
            Vector2{texture.width*scale/2.f,texture.height*scale/2.f},
            0,
            WHITE
        );
    }

    void requestChangeScale(float inChange) override
    {
        scale += inChange;
    }
};
