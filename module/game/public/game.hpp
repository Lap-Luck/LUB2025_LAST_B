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


class Game
{
public:
    Camera2D camera;
    explicit Game(GameState& inState) : state(inState) {};

    void onInitialize();
    void onUpdate(float deltaTime);
    void onDraw();

    Vec2i screenSize {};

    GameState& state;

protected:
    Vector2 ballPosition = { 100,100 };

    ObstacleMask col_mask;
    ObstacleMask col_mask3;
    ObstacleMask col_mask4;
    ObstacleMask col_m1;
    ObstacleMask col_m2;
};
