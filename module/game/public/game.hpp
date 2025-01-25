#pragma once
#include <vector>

#include "gameState.hpp"
#include "obstacle.hpp"
#include "raymath.h"
#include "vec2.hpp"

class Game;

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

    void frame(std::vector<Obstacle> &obs){
        if (IsKeyDown(KEY_RIGHT)) vel.x=Lerp(vel.x,2000.0,0.001f);
        if (IsKeyDown(KEY_LEFT)) vel.x=Lerp(vel.x,-2000.0,0.001f);

        vel.y=Lerp(vel.y,-100.0,0.02f);
        pos=Vector2Add(pos,Vector2Scale(vel,0.016));

        for (int o_id:range(obs.size())) {
            Obstacle o=obs[o_id];
            for (int s_id:range(o.segments.size())) {
                ObSegment s=o.segments[s_id];
                Vector2 A={((float)s.ax+0.5f)*20.0f,((float)s.ay+0.5f)*20.0f};
                Vector2 B={((float)s.bx+0.5f)*20.0f,((float)s.by+0.5f)*20.0f};

                Vec2f C=ClosesPointInSegment(A,B,pos);
                float d=Vector2Distance(C,pos);
                if (d<r) {
                    float pen=(r-d)*1.001;
                    Vec2f pc=pos-C;
                    pos=pos+(((pc).normalized())*pen);
                    Vec2f AB=(A-B);
                    if (AB.dotProduct(Vec2f(0,1))<0.01f) {
                        vel.y+=fmax(0.0,vel.y);
                    }
                    if (pc.dotProduct(Vec2f(vel.x,0))<0) {
                        vel.y+=fabs(vel.x)*0.5;
                        vel.x=-vel.x*0.99;
                    }

                }
            }
        }


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
