#pragma once
#include "actor.hpp"
#include "backgroundActor.hpp"
#include "doorActor.hpp"
#include "spikeActor.hpp"

inline ActorFactory ConstructAssetFactorty()
{
    return ActorFactory
    {{
        {"Spike",[](auto& state){return std::make_unique<SpikeActor>(state,Vec2f{});}},
        {"Door",[](auto& state){return std::make_unique<DoorActor>(state,Vec2f{});}},
        {"Background",[](auto& state){return std::make_unique<BackgroundActor>(state,Vec2f{});}},
    }};
}
