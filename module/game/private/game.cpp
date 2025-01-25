#include "game.hpp"

#include "obstacle.hpp"

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
    col_mask.load(LoadImage48("col_mask.png"));
    col_mask3.load(LoadImage48("col_mask3.png"));

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
        obstacles.obstacles.push_back(std::move(door));


        Obstacle button = Obstacle(&col_mask3,{300.0,-300.0},10.0f);
        button.onHit = [&,door_id](Bubble* bubble)
        {
            TraceLog(LOG_INFO,"DOOR OPEN");
            if(obstacles.getById(door_id))
                obstacles.getById(door_id)->pendingDestroy = true;
        };
        obstacles.obstacles.push_back(std::move(button));
    }

    cuts.push_back(CutLine({280.0,0.0},-50.0));

    bubbles.push_back(Bubble(
        (Vector2){100.0,600.0},
        (Vector2){0.0,-100.0},
        25.0));
    camera.rotation = 0.f;
    camera.zoom = 1.0f;
    float my=max_bubble_y(bubbles);
    camera.target= Vec2f(0.0,my);//bubbles[0].pos;
    camera.offset= Vec2f(0.0,screenSize.y*0.5);
}

void Game::onUpdate(float deltaTime)
{
    for (int b_id:range(bubbles.size())){
        Bubble& b=bubbles[b_id];
        b.frame(obstacles.obstacles,cuts);
    }

    bool cuts=true;
    while (cuts) {
        cuts=false;
        for (int b_id:range(bubbles.size())) {
            if (bubbles[b_id].cut_id!=-1) {
                Bubble cut_bubble=bubbles[b_id];
                if (cut_bubble.divided<4) {


                    std::vector<BubbleP> particlesAB[2];
                    {
                        for (int p_id:range(cut_bubble.particles.size())) {
                            BubbleP bp=cut_bubble.particles[0];
                            cut_bubble.particles.erase(cut_bubble.particles.begin());
                            particlesAB[rand()%2].push_back(bp);
                        }

                    }


                    bubbles.erase(bubbles.begin() + b_id);


                    {
                        Bubble new_bubble=Bubble(
            (Vector2){cut_bubble.pos.x+50.0f,cut_bubble.pos.y},
            (Vector2){0.0,-100.0},
            25.0-(cut_bubble.divided+1)*4.5,cut_bubble.divided+1,0);
                        new_bubble.particles.swap(particlesAB[0]);
                        bubbles.push_back(new_bubble);
                    }

                    {
                        Bubble new_bubble=Bubble(
            (Vector2){cut_bubble.pos.x-50.0f,cut_bubble.pos.y},
            (Vector2){0.0,-100.0},
            25.0-(cut_bubble.divided+1)*4.5,cut_bubble.divided+1,0);
                        new_bubble.particles.swap(particlesAB[1]);
                        bubbles.push_back(new_bubble);
                    }


                    cuts=true;
                    break;


                }

            }
        }
    }


    camera.target= Vec2f(0.0,fmin(max_bubble_y(bubbles),camera.target.y-0.3));
    obstacles.deletePending();
}

void Game::onDraw()
{
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    for (int b_id:range(bubbles.size())){
        Bubble& b=bubbles[b_id];
        b.draw();
    }

    for (int o_id:range(obstacles.obstacles.size())){
        Obstacle& o=obstacles.obstacles[o_id];
        o.draw();
    }

    for (int c_id:range(cuts.size())){
        CutLine& cl=cuts[c_id];
        cl.draw();
    }


    EndMode2D();

    DrawFPS(10, 10);
}
