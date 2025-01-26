#pragma once

class ButtonActor : public Actor
{
public:
    ACTOR_BODY(ButtonActor);

    ButtonActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~ButtonActor(){}

    std::string signal_name="a";

    void onPlaced() override
    {
        Obstacle obstacle = Obstacle(&state.assets.spikeMask,pos,3.0f);

        obstacle.onHit = [this](Bubble* bubble)
        {
            //TraceLog(LOG_INFO,"DOOR OPEN");
            state.last_signal=signal_name;
        };



        SpawnnObstacle(std::move(obstacle));
    }

    void onDraw() override
    {
        auto& texture = state.assets.obstaclesTexturesPlus[1].img;
        DrawTexturePro(texture, { 0.0f, 0.0f, (float)texture.width, (float)texture.height },
            {pos.x, pos.y, (float)texture.width/8, (float)texture.height/8},
            {0,0}, 0.0f, WHITE);
    }
    void onSerialize(ISerialize* inSerialize) override {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyString("signal_name",signal_name);
    }
};
