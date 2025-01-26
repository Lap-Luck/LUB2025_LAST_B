#include "game.hpp"

#include <actorSerializeHelpers.hpp>
#include <iostream>

#include "obstacle.hpp"
#include "actor/spikeActor.hpp"

namespace{
    float max_bubble_y(std::vector<Bubble>b) {
        float record=b[0].pos.y;
        for (int b_id:range(b.size())) {
            float v=b[b_id].pos.y;
            if (v<record) {
                record=v;
            }
        }
        return record;
    }
}


void Game::onInitialize()
{
    state.bubbles.values.clear();
    state.cuts.values.clear();
    state.obstacles.values.clear();


    /*state.actors.values.push_back(std::make_unique<SpikeActor>(state,Vec2f{0,0}));
    state.actors.values.push_back(std::make_unique<SpikeActor>(state,Vec2f{100,-100}));

    col_mask=LoadObstacleMask(LoadImage48("col_mask.png"));
    col_mask3=LoadObstacleMask(LoadImage48("col_mask3.png"));

    col_mask4=LoadObstacleMask(LoadImage48("col_long.png"));

    auto cmasks=LoadObstacleMasks(LoadImage48("szczupak_final_mask.png"),2);

    col_m1=cmasks[0];
    col_m2=cmasks[1];

    obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,250.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{300.0,0.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{300.0,-300.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{300.0,-600.0},10.0f));


    obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,120.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,-20.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,-160.0},10.0f));
    //HELP IT IS BAD CODE
    {
        Obstacle door = Obstacle(&col_mask,{200.0,-400.0},10.0f);
        Obstacle::ObstacleId door_id= door.unique_id;
        state.obstacles.values.push_back(std::move(door));


        Obstacle button = Obstacle(&col_mask3,{300.0,-300.0},10.0f);
        button.onHit = [&,door_id](Bubble* bubble)
        {
            TraceLog(LOG_INFO,"DOOR OPEN");
            if(state.obstacles.getById(door_id))
                state.obstacles.getById(door_id)->flags.pendingDestroy = true;
        };
        state.obstacles.values.push_back(std::move(button));

        Obstacle kill = Obstacle(&col_mask3,{100.0,-300.0},10.0f);
        kill.onHit = [&,door_id](Bubble* bubble)
        {
            bubble->flags.pendingDestroy = true;
        };

        state.obstacles.values.push_back(std::move(kill));
    }

    {
        Obstacle longObstacle = Obstacle(&col_mask4,{200.0,-550.0},10.0f);
        state.obstacles.values.push_back(std::move(longObstacle));
    }

    {
        Obstacle m1Obstacle = Obstacle(&col_m1,{200.0,-750.0},10.0f);
        state.obstacles.values.push_back(std::move(m1Obstacle));
        Obstacle m2Obstacle = Obstacle(&col_m2,{200.0,-750.0},10.0f);
        state.obstacles.values.push_back(std::move(m2Obstacle));
    }

    state.cuts.values.push_back(CutLine({280.0,0.0},-50.0));
    */
    camera.rotation = 0.f;
    if (state.levelConfig.spawnBubble)
    {
        state.bubbles.values.push_back(Bubble(
            (Vector2){0,0.0},
            (Vector2){0.0,-100.0},
            25.0));
    }

    SetSoundVolume(state.assets.sound[state.config.ObstacleOnHitSound],state.config.ObstacleOnHitVolume);

    for (auto& it : state.actors.values)
    {
        it->onPlaced();
    }
}

void Game::onUpdate(float deltaTime)
{
    state.temp.screenSize = screenSize;
    Vec2f mousePos;
    mousePos.x = (GetMousePosition().x - winPos.x);
    mousePos.y = (GetMousePosition().y - winPos.y);
    state.temp.mouseWorldPos = GetScreenToWorld2D(Vector2(mousePos), camera);

    for (auto& it : state.actors.values)
    {
        it->onUpdate();
    }

    camera.zoom = screenSize.x/1440.f;
    if (state.levelConfig.spawnBubble)
    {
        float CAMERA_VEL=state.config.minimalCameraSpeed;
        cameraHeigth=fmin(max_bubble_y(state.bubbles.values),cameraHeigth-CAMERA_VEL);
        camera.target= Vec2f(0,cameraHeigth);
    }
    else
    {
        camera.target= Vec2f(0,0);
    }

    camera.offset= Vec2f(screenSize.x/2,screenSize.y*0.5);

    for (int b_id:range(state.bubbles.values.size()))
    {
        Bubble& b=state.bubbles.values[b_id];
        b.frame(state.obstacles.values,state.cuts.values);
    }

    bool cuts=true;
    while (cuts) {
        cuts=false;
        for (int b_id:range(state.bubbles.values.size())) {
            if (state.bubbles.values[b_id].cut_id!=-1) {
                Bubble cut_bubble=state.bubbles.values[b_id];
                if (cut_bubble.divided<4) {
                    std::vector<BubbleP> particlesAB[2];
                    {
                        for (int p_id:range(cut_bubble.particles.size())) {
                            BubbleP bp=cut_bubble.particles[0];
                            cut_bubble.particles.erase(cut_bubble.particles.begin());
                            particlesAB[rand()%2].push_back(bp);
                        }

                    }


                    state.bubbles.values.erase(state.bubbles.values.begin() + b_id);


                    {
                        Bubble new_bubble=Bubble(
            (Vector2){cut_bubble.pos.x+50.0f,cut_bubble.pos.y},
            (Vector2){0.0,-100.0},
            25.0-(cut_bubble.divided+1)*4.5,cut_bubble.divided+1,0);
                        new_bubble.particles.swap(particlesAB[0]);
                        state.bubbles.values.push_back(new_bubble);
                    }

                    {
                        Bubble new_bubble=Bubble(
            (Vector2){cut_bubble.pos.x-50.0f,cut_bubble.pos.y},
            (Vector2){0.0,-100.0},
            25.0-(cut_bubble.divided+1)*4.5,cut_bubble.divided+1,0);
                        new_bubble.particles.swap(particlesAB[1]);
                        state.bubbles.values.push_back(new_bubble);
                    }
                    cuts=true;
                    break;
                }
            }
        }
    }

    state.obstacles.deletePending();
    state.bubbles.deletePending();
    state.actors.deletePending();
    state.cuts.deletePending();
    if (state.levelConfig.spawnBubble && IsGameOver()) {
        state.sceneControl.changeLevel = "gameOver";
    }
    if (state.levelConfig.spawnBubble && IsWinOver()) {
        state.sceneControl.changeLevel = "winOver";
    }
    if (state.sceneControl.changeLevel)
    {
        loadFromFile(state.sceneControl.changeLevel.value(),state);
        onInitialize();

        state.sceneControl.changeLevel = {};
    }
}

bool Game::IsGameOver() {
    bool game_over=true;
    for (int b_id:range(state.bubbles.values.size())) {
        float h=state.bubbles.values[b_id].pos.y;
        if (h<cameraHeigth+camera.offset.y*2) {
            game_over=false;
        }
    }
    return game_over;
}

bool Game::IsWinOver() {
    bool winOver=false;
    for (int b_id:range(state.bubbles.values.size())) {
        float h=state.bubbles.values[b_id].pos.y;
        if (h<-state.levelConfig.levelHeight*1440) {
            winOver=true;
        }
    }
    return winOver;
}

void Game::onDraw()
{
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    for (auto& it : state.actors.values)
    {
        it->onDraw();
    }

    for (int b_id:range(state.bubbles.values.size())){
        Bubble& b=state.bubbles.values[b_id];
        b.draw();
    }

    if (state.config.debugDraw)
    {
        for (int o_id:range(state.obstacles.values.size())){
            Obstacle& o=state.obstacles.values[o_id];
            o.draw();
        }

        for (int c_id:range(state.cuts.values.size())){
            CutLine& cl=state.cuts.values[c_id];
            cl.draw();
        }
    }


    EndMode2D();

    DrawFPS(10, 10);
}
