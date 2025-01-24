#pragma once
#include "gameState.hpp"
#include "vec2.hpp"

class Game
{
public:
    explicit Game(GameState& inState) : state(inState) {}

    void onInitialize();
    void onUpdate(float deltaTime);
    void onDraw();

    Vec2i screenSize {};

protected:
    GameState& state;
    Vector2 ballPosition = { 100,100 };

};
