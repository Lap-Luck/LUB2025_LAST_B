#pragma once

class DoorActor : public Actor
{
public:
    CutLine::CutLineId cutId {};
    Obstacle::ObstacleId  obstalceId {};

    DoorActor(GameState& inState,Vec2f inPos) : DoorActor(inState,inPos) {}
    ~DoorActor()
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

        Obstacle obstacle = Obstacle(&state.assets.spikeMask,pos,3.0f);
        obstalceId = obstacle.unique_id;
        state.obstacles.values.push_back(std::move(obstacle));
    }

    void onDraw() override
    {
        auto& texture = state.assets.spike;
        DrawTexturePro(state.assets.spike, { 0.0f, 0.0f, (float)texture.width, (float)texture.height },
            {0.0f, 0.0f, (float)texture.width/8, (float)texture.height/8},
            {0,0}, 0.0f, WHITE);
    }
};
