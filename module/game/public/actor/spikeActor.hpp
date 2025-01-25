#pragma once
#include "actor.hpp"
#include "gameState.hpp"
#include "vec2.hpp"

class SpikeActor : public Actor
{
public:
    Vec2f pos {};
    CutLine::CutLineId cutId;

    SpikeActor(GameState& inState,Vec2f inPos) : Actor(inState), pos(inPos) {}

    void onPlaced() override
    {
        CutLine cut = CutLine{pos,200};
        cutId = cut.unique_id;
        state.cuts.values.push_back(std::move(cut));
    }

    void onDraw() override
    {
        auto& texture = state.assets.spike;
        DrawTexturePro(state.assets.spike, { 0.0f, 0.0f, (float)texture.width, (float)texture.height },
            {0.0f, 0.0f, (float)texture.width/8, (float)texture.height/8},
            {0,0}, 0.0f, WHITE);
    }
};
