#pragma once
#include <memory>
#include <vector>

#include "actor.hpp"
#include "gameState.hpp"
#include "obstacle.hpp"
#include "raymath.h"
#include "vec2.hpp"
#include "inputManager.hpp"
#include "bubble.hpp"


namespace{
    Image LoadImage48(char* path){
        Image img=LoadImage(path);
        ImageFormat(&img,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        return img;
    }
};


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
    std::vector<std::unique_ptr<Actor>> values;

    void deletePending()
    {
        std::erase_if(values, [](auto& x)
        {
            return x->flags.pendingDestroy;
        });
    }
};

class Game
{
public:
    Camera2D camera;
    explicit Game(GameState& inState) : state(inState) {};

    void onInitialize();
    void onUpdate(float deltaTime);
    void onDraw();

    Vec2i screenSize {};

    BubblesContainer bubbles {};
    ObstacleContainer obstacles {};
    ActorContainer actors {};
    std::vector<CutLine> cuts;

protected:
    GameState& state;
    Vector2 ballPosition = { 100,100 };

    ObstacleMask col_mask;
    ObstacleMask col_mask3;
};
