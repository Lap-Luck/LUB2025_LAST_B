#pragma once

class DoorActor : public Actor
{
public:
    ACTOR_BODY(DoorActor);

    DoorActor(GameState& inState,Vec2f inPos) : Actor(inState,inPos) {}
    ~DoorActor(){}

    Obstacle::ObstacleId colision_id;
    std::string signal="a";
    float scale=1.0f;
    bool active=true;

    void onPlaced() override
    {
        auto o=Obstacle(&state.assets.dooro,pos,scale*50.0);
        colision_id=o.unique_id;
        SpawnnObstacle(o);
    }

    void onDraw() override
    {
        if (active) {
            auto& texture = state.assets.doort;
            DrawTexturePro(state.assets.doort, { 0.0f, 0.0f, (float)texture.width, (float)texture.height },
                {pos.x, pos.y, (float)texture.width*scale, (float)texture.height*scale},
                {0,0}, 0.0f, WHITE);
        }

    }

    void onUpdate() override
    {
        if (state.last_signal==signal) {
            active=false;
            state.obstacles.getById(colision_id)->active=false;
            //this->flags.pendingDestroy =true;
        }
    }

    void onSerialize(ISerialize* inSerialize) override {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyString("signal_name",signal);
        inSerialize->propertyFloat("scale",scale);
    }
};
