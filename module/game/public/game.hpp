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




class Game
{
public:
    Camera2D camera;
    explicit Game(GameState& inState) : state(inState) {}

    void onInitialize();
    void onUpdate(float deltaTime);
    void onDraw();

    Vec2i screenSize {};

    std::vector<Bubble> bubbles;
    std::vector<Obstacle> obstacles;
    std::vector<CutLine> cuts;
    std::vector<CollsionTriger> collsionTrigers;

protected:
    GameState& state;
    Vector2 ballPosition = { 100,100 };

};
