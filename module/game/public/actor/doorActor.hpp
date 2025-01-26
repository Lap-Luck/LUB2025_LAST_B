#pragma once

class DoorActor : public Actor
{
public:
    ACTOR_BODY(DoorActor);

    DoorActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~DoorActor(){}

    std::string signal="a";
    float scale=1.0f;

    void onPlaced() override
    {
        SpawnnObstacle(Obstacle(&state.assets.dooro,pos,scale*3.0f));
    }

    void onDraw() override
    {
        auto& texture = state.assets.doort;
        DrawTexturePro(state.assets.doort, { 0.0f, 0.0f, (float)texture.width, (float)texture.height },
            {pos.x, pos.y, (float)texture.width*scale/8, (float)texture.height*scale/8},
            {0,0}, 0.0f, WHITE);
    }

    void onUpdate() override
    {
        if (state.last_signal==signal) {
            this->flags.pendingDestroy =true;
        }
    }

    void onSerialize(ISerialize* inSerialize) override {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyString("signal_name",signal);
        inSerialize->propertyFloat("scale",scale);
    }
};
