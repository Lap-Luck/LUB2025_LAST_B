#pragma once

class ObstacleActor : public Actor
{
public:
    ACTOR_BODY(ObstacleActor);

    int grafix_id=0;
    bool flag_mirror=false;

    ObstacleActor(GameState& inState,Vec2f inPos,int _grafix_id =0 ) : Actor(inState,inPos),grafix_id(_grafix_id){}
    ~ObstacleActor(){}

    Texture2DPlus& getData() {
        if (flag_mirror) {
            return state.assets.obstaclesTexturesPlusR[grafix_id];
        }
        return state.assets.obstaclesTexturesPlus[grafix_id];
    }

    void onPlaced() override
    {
        ObstacleMask& om=getData().masks[0];
        float sx=getData().obstaclePixelsSizeX*1.0f/8.0f;
        SpawnnObstacle(Obstacle(&om,pos,sx));

    }

    void onDraw() override {
        auto& texture = getData().img;

        DrawTextureEx(texture, {pos.x,pos.y}, 0.0f,1.0f/8.0f,WHITE);
    }

     void onSerialize(ISerialize* inSerialize) override
    {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyInt("grafix_id",grafix_id);
        if (grafix_id>=state.assets.obstaclesTexturesPlus.size()) {
            grafix_id=state.assets.obstaclesTexturesPlus.size()-1;
        }


        std::string s="NormalOrientation";
        if (flag_mirror) s="FlipHorizontal";
        inSerialize->propertyEnum("orientation",{"NormalOrientation","FlipHorizontal"},s);
        flag_mirror = s=="FlipHorizontal";
    }

};
