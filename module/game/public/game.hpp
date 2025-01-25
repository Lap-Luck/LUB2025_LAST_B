#pragma once
#include <vector>

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
    std::vector<Obstacle> obstacles;
    Obstacle* getById(Obstacle::ObstacleId id)
    {
        for(auto& it : obstacles)
        {
            if (it.unique_id == id)
                return &it;
        }
        return nullptr;
    }

    void deletePending()
    {
        std::erase_if(obstacles, [](auto& x)
        {
            return x.pendingDestroy;
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

    std::vector<Bubble> bubbles;
    ObstacleContainer obstacles;
    std::vector<CutLine> cuts;

protected:
    GameState& state;
    Vector2 ballPosition = { 100,100 };

    ObstacleMask col_mask;
    ObstacleMask col_mask3;
};
