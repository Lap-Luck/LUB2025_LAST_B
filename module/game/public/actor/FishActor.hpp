#pragma once

//ERROR NOT WORKING DYNAMIC COLISION SHAPE WHEN RETURING!!

class FishActor : public Actor
{
public:
    ACTOR_BODY(FishActor);
    FishActor(GameState& inState,Vec2f inPos ) : Actor(inState,inPos){};
    ~FishActor(){};

    bool in_game=false;
    float to_move=-1000.0f;

    Obstacle::ObstacleId id_body;
    Obstacle::ObstacleId id_kill;
    Obstacle::ObstacleId id_bodyR;
    Obstacle::ObstacleId id_killR;

    Vec2f A;
    Vec2f B;
    bool dir=true;

    Vec2f target() {
        if (dir) {
            return B;
        }
        return A;
    }


    void onPlaced() override
    {
        //auto cmasks=LoadObstacleMasks(LoadImage48("szczupak_final_mask.png"),2);

        bool not_placed=false;
        //state.assets.fish1[0]=cmasks[0];
        //state.assets.fish2=cmasks[1];

        Obstacle body = Obstacle(&state.assets.fish1,{pos.x,pos.y},10.0f);
        id_body=body.unique_id;
        Obstacle kill = Obstacle(&state.assets.fish2,{pos.x,pos.y},10.0f);
        id_kill=kill.unique_id;
        Obstacle bodyR = Obstacle(&state.assets.fish1R,{pos.x,pos.y},10.0f);
        id_bodyR=bodyR.unique_id;
        Obstacle killR = Obstacle(&state.assets.fish2R,{pos.x,pos.y},10.0f);
        id_killR=killR.unique_id;
        killR.onHit = [](Bubble* bubble)
        {
            bubble->flags.pendingDestroy = true;
        };
        kill.onHit = [](Bubble* bubble)
        {
            bubble->flags.pendingDestroy = true;
        };

        state.obstacles.values.push_back(std::move(body));
        state.obstacles.values.push_back(std::move(kill));
        state.obstacles.values.push_back(std::move(bodyR));
        state.obstacles.values.push_back(std::move(killR));
        A=pos;
        B=A+Vec2f(to_move,0.0f);
    }
    void UpdateCol() {
        if (dir) {

        }
    }
    void onUpdate() override {

        Vec2f move;

        in_game=true;
        if (dir) {
            move=(B-A).normalized()*1.6f;
            if ((B-pos).length()<10.0f) {
                dir=!dir;
                UpdateCol();
            }
        }
        else {
            move=(A-B).normalized()*1.6f;
            if ((A-pos).length()<10.0f) {
                dir=!dir;
                UpdateCol();
            }
        }
        pos=pos+move;
        if (move.x>0) {
            state.obstacles.getById(id_body)->active=false;
            state.obstacles.getById(id_kill)->active=false;
            state.obstacles.getById(id_bodyR)->active=true;
            state.obstacles.getById(id_killR)->active=true;
        }
        else {
            state.obstacles.getById(id_body)->active=true;
            state.obstacles.getById(id_kill)->active=true;
            state.obstacles.getById(id_bodyR)->active=false;
            state.obstacles.getById(id_killR)->active=false;
        }
        state.obstacles.getById(id_body)->pos=pos;
        state.obstacles.getById(id_kill)->pos=pos;
        state.obstacles.getById(id_bodyR)->pos=pos;
        state.obstacles.getById(id_killR)->pos=pos;
    }

    void onDraw() override {
        if (target().x<pos.x) {
            DrawTextureEx(state.assets.szczupakf, {pos.x,pos.y}, 0.0f,1.0f,WHITE);
        }
        else {
            DrawTextureEx(state.assets.szczupakfR, {pos.x,pos.y}, 0.0f,1.0f,WHITE);
        }

        if(!in_game){
            DrawLineEx({pos.x,pos.y}, {pos.x+to_move,pos.y}, 10.0, BLACK);
        }
    }
    void onSerialize(ISerialize* inSerialize) override
    {
        Actor::onSerialize(inSerialize);
        inSerialize->propertyFloat("to_move",to_move);
    }

};
