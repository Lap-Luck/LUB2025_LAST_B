#include "game.hpp"

#include "obstacle.hpp"

void Game::onInitialize()
{
    obstacles.push_back(Obstacle(LoadImage48("col_mask.png")));
    bubbles.push_back(Bubble(
        (Vector2){100.0,600.0},
        (Vector2){0.0,-100.0},
        50.0));
}

void Game::onUpdate(float deltaTime)
{
    for (int b_id:range(bubbles.size())){
        Bubble& b=bubbles[b_id];
        b.frame(obstacles);
    }
}

void Game::onDraw()
{
    ClearBackground(RAYWHITE);

    for (int b_id:range(bubbles.size())){
        Bubble& b=bubbles[b_id];
        DrawCircleV(b.pos,b.r, MAROON);
    }

    for (int o_id:range(obstacles.size())){
        Obstacle& o=obstacles[o_id];
        o.draw();
    }


    DrawFPS(10, 10);
}
