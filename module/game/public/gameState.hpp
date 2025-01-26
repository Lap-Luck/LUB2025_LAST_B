#pragma once
#include <memory>
#include <vector>

#include "assetsContainer.hpp"
#include "bubble.hpp"
#include "obstacle.hpp"
#include "physicConfig.hpp"
#include "raylib.h"

#include "actor.hpp"
#include "gameConfig.hpp"

class ObstacleContainer
{
public:
    std::vector<Obstacle> values;
    Obstacle* getById(Obstacle::ObstacleId id)
    {
        for(auto& it : values)
        {
            if (it.unique_id == id)
                return &it;
        }
        return nullptr;
    }

    void deletePending()
    {
        std::erase_if(values, [](auto& x)
        {
            return x.flags.pendingDestroy;
        });
    }
};

class CutLineContainer
{
public:
    std::vector<CutLine> values;
    CutLine* getById(CutLine::CutLineId id)
    {
        for(auto& it : values)
        {
            if (it.unique_id == id)
                return &it;
        }
        return nullptr;
    }

    void deletePending()
    {
        std::erase_if(values, [](auto& x)
        {
            return x.flags.pendingDestroy;
        });
    }
};

class BubblesContainer
{
public:

    std::vector<Bubble> values;

    void deletePending()
    {
        std::erase_if(values, [](auto& x)
        {
            return x.flags.pendingDestroy;
        });
    }
};

class ActorContainer
{
public:
    std::vector<std::shared_ptr<Actor>> values;

    void deletePending()
    {
        std::erase_if(values, [](auto& x)
        {
            return x->flags.pendingDestroy;
        });
    }
};

class GameState
{
public:
    GameConfig config;

    AssetsContainer assets;
    ActorFactory actorFactory {};

    BubblesContainer bubbles {};
    ObstacleContainer obstacles {};
    CutLineContainer cuts {};
    ActorContainer actors {};
    std::string last_signal;
};
