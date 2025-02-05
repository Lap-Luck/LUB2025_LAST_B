#pragma once
#include "actor.hpp"
#include "backgroundActor.hpp"
#include "buttonActor.hpp"
#include "doorActor.hpp"
#include "FishActor.hpp"
#include "MenuButtonActor.hpp"
#include "ObstacleActor.hpp"
#include "SoundActor.hpp"
#include "spikeActor.hpp"

template<typename T>
inline ActorFactoryEntry GenEntry(std::function<std::unique_ptr<Actor>(class GameState&)> construct)
{
    return {T::ClassName,construct};
}

inline ActorFactory ConstructAssetFactorty()
{
    return ActorFactory
    {{
        GenEntry<SpikeActor>([](auto& state){return std::make_unique<SpikeActor>(state,Vec2f{});}),
        GenEntry<DoorActor>([](auto& state){return std::make_unique<DoorActor>(state,Vec2f{});}),
        GenEntry<ObstacleActor>([](auto& state){return std::make_unique<ObstacleActor>(state,Vec2f{},0);}),
        GenEntry<BackgroundActor>([](auto& state){return std::make_unique<BackgroundActor>(state,Vec2f{});}),
        GenEntry<FishActor>([](auto& state){return std::make_unique<FishActor>(state,Vec2f{});}),
        GenEntry<ButtonActor>([](auto& state){return std::make_unique<ButtonActor>(state,Vec2f{});}),
        GenEntry<MenuButtonActor>([](auto& state){return std::make_unique<MenuButtonActor>(state,Vec2f{});}),
        GenEntry<SoundActor>([](auto& state){return std::make_unique<SoundActor>(state,Vec2f{});})

    }};
}
