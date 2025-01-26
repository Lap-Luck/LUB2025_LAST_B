#pragma once

class ObstacleActor : public Actor, public IActorModifyParam
{
public:
    ACTOR_BODY(ObstacleActor);
    float scale=1.0f;
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
        float sx=((float)getData().obstaclePixelsSizeX)*1.0f*scale;
        auto& texture = getData().img;
        auto* ob = SpawnnObstacle(Obstacle(&om,Vector2(pos-Vec2f{texture.width*scale/2.f,texture.height*scale/2.f}),sx));
        ob->onHit = [&](class Bubble* b)
        {
            //PlaySound(state.assets.sound[state.config.]);
        };
    }

    void onDraw() override {
        auto& texture = getData().img;

        DrawTexturePro(
            texture,
            {0,0,(float)texture.width,(float)texture.height},
            {pos.x,pos.y,texture.width*scale,texture.height*scale},
            Vector2{texture.width*scale/2.f,texture.height*scale/2.f},
            0,
            WHITE
        );
    }

     void onSerialize(ISerialize* inSerialize) override
    {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyInt("grafix_id",grafix_id);
        inSerialize->propertyFloat("scale",scale);

        if (grafix_id>=state.assets.obstaclesTexturesPlus.size()) {
            grafix_id=state.assets.obstaclesTexturesPlus.size()-1;
        }


        std::string s="NormalOrientation";
        if (flag_mirror) s="FlipHorizontal";
        inSerialize->propertyEnum("orientation",{"NormalOrientation","FlipHorizontal"},s);
        flag_mirror = s=="FlipHorizontal";



        //inSerialize->propertyEnum("soundOnHit",state.assets.soundKeys,soundOnHit);
    }

    void requestChangeScale(float inChange) override
    {
        scale += inChange;
    }

    void requestChangeRotation(float inChange) override
    {
        flag_mirror = inChange > 0 ? true : false;
    }
};
