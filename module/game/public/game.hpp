#pragma once
#include <vector>

#include "gameState.hpp"
#include "obstacle.hpp"
#include "raymath.h"
#include "vec2.hpp"


class Bubble
{
public:
    Vector2 pos;
    Vector2 vel;
    float r;


    Bubble(Vector2 _pos,Vector2 _vel,float _r){
        this->pos=_pos;
        this->vel=_vel;
        this->r=_r;
    }

    void frame(){
        if (IsKeyDown(KEY_RIGHT)) vel.x=Lerp(vel.x,100.0,0.1f);
        if (IsKeyDown(KEY_LEFT)) vel.x=Lerp(vel.x,-100.0,0.1f);

        pos=Vector2Add(pos,Vector2Scale(vel,0.016));
    }
};



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

    explicit Game(GameState& inState) : state(inState) {}

    void onInitialize();
    void onUpdate(float deltaTime);
    void onDraw();

    Vec2i screenSize {};

    std::vector<Bubble> bubbles;
    std::vector<Obstacle> obstacles;

protected:
    GameState& state;
    Vector2 ballPosition = { 100,100 };

};
