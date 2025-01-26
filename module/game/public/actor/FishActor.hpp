#pragma once

class FishActor : public Actor
{
public:
    ACTOR_BODY(FishActor);
    FishActor(GameState& inState,Vec2f inPos ) : Actor(inState,inPos){};
    ~FishActor(){};

    Obstacle::ObstacleId id_body;
    Obstacle::ObstacleId id_kill;


    void onPlaced() override
    {
        auto cmasks=LoadObstacleMasks(LoadImage48("szczupak_final_mask.png"),2);

        state.assets.fish1=cmasks[0];
        state.assets.fish2=cmasks[1];

        Obstacle body = Obstacle(&state.assets.fish1,{pos.x,pos.y},10.0f);
        id_body=body.unique_id;
        Obstacle kill = Obstacle(&state.assets.fish2,{pos.x,pos.y},10.0f);
        id_kill=kill.unique_id;
        kill.onHit = [](Bubble* bubble)
        {
            bubble->flags.pendingDestroy = true;
        };

        state.obstacles.values.push_back(std::move(body));
        state.obstacles.values.push_back(std::move(kill));

    }
    void onUpdate() override {
        pos.y+=0.15f;
        pos.x-=0.5f;
        state.obstacles.getById(id_body)->pos=pos;
        state.obstacles.getById(id_kill)->pos=pos;
    }

    void onDraw() override {

        DrawTextureEx(state.assets.szczupakf, {pos.x,pos.y}, 0.0f,1.0f,WHITE);
    }


};
