#pragma once
#include "actor.hpp"
#include "gameState.hpp"
#include "vec2.hpp"



class SoundActor : public Actor
{
public:
    ACTOR_BODY(SoundActor);

    std::string selectedSound = "unknown";
    float volume = 1;
    bool loop = false;


    SoundActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~SoundActor() override
    {
        if (IsSoundPlaying(state.assets.sound[selectedSound]))
            StopSound(state.assets.sound[selectedSound]);
    }

    void onPlaced() override
    {
        PlaySound(state.assets.sound[selectedSound]);
        SetSoundVolume(state.assets.sound[selectedSound],volume);
    }

    void onSerialize(ISerialize* inSerialize) override
    {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyEnum("selectedSound",state.assets.soundKeys,selectedSound);
        inSerialize->propertyFloat("volume",volume);
        inSerialize->propertyBool("loop",loop);
    }

    void onUpdate() override
    {
        if (!IsSoundPlaying(state.assets.sound[selectedSound]))
            PlaySound(state.assets.sound[selectedSound]);
    }

    void onDraw() override
    {

    }
};
