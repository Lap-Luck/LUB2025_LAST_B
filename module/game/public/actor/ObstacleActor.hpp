#pragma once

class ObstacleActor : public Actor
{
public:
    int grafix_id=0;

    ObstacleActor(GameState& inState,Vec2f inPos,int _grafix_id ) : Actor(inState,inPos),grafix_id(_grafix_id){}
    ~ObstacleActor(){}

    void onPlaced() override
    {
        ObstacleMask om=state.assets.obstaclesTexturesPlus[grafix_id].masks[0];
        SpawnnObstacle(Obstacle(&om,pos,10.0f));

    }

    void onDraw() override {
        auto& texture = state.assets.obstaclesTexturesPlus[grafix_id].img;
        DrawTextureEx(state.assets.spike, {pos.x,pos.y}, 0.0f,1.0f/8.0f,WHITE);
    }

     void onSerialize(ISerialize* inSerialize) override
    {
        Actor::onSerialize(inSerialize);
        float temp = grafix_id;
        inSerialize->propertyFloat("grafix_id",temp);
        grafix_id = temp;
    }

};
