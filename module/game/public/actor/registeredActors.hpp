#pragma once
#include "actor.hpp"
#include "backgroundActor.hpp"
#include "doorActor.hpp"
#include "ObstacleActor.hpp"
#include "spikeActor.hpp"

inline ActorFactory ConstructAssetFactorty()
{
    return ActorFactory
    {{
        {"Spike",[](auto& state){return std::make_unique<SpikeActor>(state,Vec2f{});}},
        {"Door",[](auto& state){return std::make_unique<DoorActor>(state,Vec2f{});}},
        {"Obstacle",[](auto& state){return std::make_unique<ObstacleActor>(state,Vec2f{},0);}},
        {"Background",[](auto& state){return std::make_unique<BackgroundActor>(state,Vec2f{});}},
    }};
}
