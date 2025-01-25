#pragma once

class Actor
{
public:
    virtual ~Actor() = default;

    virtual void onPlaced() = 0;
    virtual void onDraw() = 0;

    struct
    {
        bool pendingDestroy {false};
    } flags;
};