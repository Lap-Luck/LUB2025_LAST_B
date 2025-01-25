#pragma once
#include "actor.hpp"
#include "gameState.hpp"
#include "vec2.hpp"



class SpikeActor : public Actor
{
public:
    CutLine::CutLineId cutId {};
    Obstacle::ObstacleId  obstalceId {};
    float scale=1.0f/8.0f;

    SpikeActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~SpikeActor()
    {
        if(state.cuts.getById(cutId))
            state.cuts.getById(cutId)->flags.pendingDestroy = true;
        if(state.obstacles.getById(obstalceId))
            state.obstacles.getById(obstalceId)->flags.pendingDestroy = true;
    }

    void onPlaced() override
    {
        CutLine cut = CutLine{pos+Vec2f{50,0},100};
        cutId = cut.unique_id;
        state.cuts.values.push_back(std::move(cut));

        Obstacle obstacle = Obstacle(&state.assets.spikeMask,pos,3.0f*8.0f*scale);
        obstalceId = obstacle.unique_id;
        state.obstacles.values.push_back(std::move(obstacle));
    }

    void onDraw() override
    {
        auto& texture = state.assets.spike;
        DrawTextureEx(state.assets.spike, {pos.x, pos.y}, 0.0, scale , WHITE);
    }

    void onSerialize(ISerialize* inSerialize) override
    {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyFloat("scale",scale);
    }

};
