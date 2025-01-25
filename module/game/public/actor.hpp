#pragma once
#include "vec2.hpp"

class GameState;

class Actor
{
public:
    virtual ~Actor() = default;
    Actor(GameState& inGameState,Vec2f inPos) : state(inGameState), pos(inPos) {};

    virtual void onPlaced() = 0;
    virtual void onDraw() = 0;

    struct
    {
        bool pendingDestroy {false};
    } flags;

    Vec2f pos {};
    GameState& state;
};