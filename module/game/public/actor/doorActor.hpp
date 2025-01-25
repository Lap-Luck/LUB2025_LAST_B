#pragma once

class DoorActor : public Actor
{
public:
    ACTOR_BODY(DoorActor);

    DoorActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~DoorActor(){}

    void onPlaced() override
    {

        CutLine cut = CutLine{pos+Vec2f{50,0},100};
        SpawnnCutLine(cut);



        auto cutId = cut.unique_id;
        state.cuts.values.push_back(std::move(cut));

        Obstacle obstacle = Obstacle(&state.assets.spikeMask,pos,3.0f);
        auto obstalceId = obstacle.unique_id;
        state.obstacles.values.push_back(std::move(obstacle));
    }

    void onDraw() override
    {
        auto& texture = state.assets.spike;
        DrawTexturePro(state.assets.spike, { 0.0f, 0.0f, (float)texture.width, (float)texture.height },
            {pos.x, pos.y, (float)texture.width/8, (float)texture.height/8},
            {0,0}, 0.0f, WHITE);
    }
};
