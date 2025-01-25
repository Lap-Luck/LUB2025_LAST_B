#include "game.hpp"

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
    state.actors.values.push_back(std::make_unique<SpikeActor>(state,Vec2f{0,0}));
    state.actors.values.push_back(std::make_unique<SpikeActor>(state,Vec2f{100,-100}));

    col_mask=LoadObstacleMask(LoadImage48("col_mask.png"));
    col_mask3=LoadObstacleMask(LoadImage48("col_mask3.png"));

    col_mask4=LoadObstacleMask(LoadImage48("col_long.png"));

    /*obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,250.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{300.0,0.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{300.0,-300.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{300.0,-600.0},10.0f));


    obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,120.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,-20.0},10.0f));
    obstacles.obstacles.push_back(Obstacle(&col_mask,{0.0,-160.0},10.0f));*/
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

    state.cuts.values.push_back(CutLine({280.0,0.0},-50.0));

    state.bubbles.values.push_back(Bubble(
        (Vector2){0,600.0},
        (Vector2){0.0,-100.0},
        25.0));
    camera.rotation = 0.f;

    for (auto& it : state.actors.values)
    {
        it->onPlaced();
    }
}

void Game::onUpdate(float deltaTime)
{
    std::cout << screenSize.x << std::endl;
    camera.zoom = screenSize.x/1000.f;
    float my=max_bubble_y(state.bubbles.values);
    camera.target= Vec2f(0,my);
    camera.offset= Vec2f(screenSize.x/2,screenSize.y*0.5);

    for (int b_id:range(state.bubbles.values.size())){
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


    camera.target= Vec2f(0.0,fmin(max_bubble_y(state.bubbles.values),camera.target.y-0.3));

    state.obstacles.deletePending();
    state.bubbles.deletePending();
    state.actors.deletePending();
    state.cuts.deletePending();
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

    for (int o_id:range(state.obstacles.values.size())){
        Obstacle& o=state.obstacles.values[o_id];
        o.draw();
    }

    for (int c_id:range(state.cuts.values.size())){
        CutLine& cl=state.cuts.values[c_id];
        cl.draw();
    }


    EndMode2D();

    DrawFPS(10, 10);
}
