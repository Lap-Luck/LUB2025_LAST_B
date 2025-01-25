#pragma once

class GameState;

class Actor
{
public:
    virtual ~Actor() = default;
    Actor(GameState& inGameState) : state(inGameState) {};

    virtual void onPlaced() = 0;
    virtual void onDraw() = 0;

    struct
    {
        bool pendingDestroy {false};
    } flags;

    GameState& state;
};