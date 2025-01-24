#include "game.hpp"

#include "obstacle.hpp"

void Game::onInitialize()
{
    obstacles.push_back(Obstacle(LoadImage48("col_mask.png")));
    bubbles.push_back(Bubble(
        (Vector2){100.0,900.0},
        (Vector2){0.0,-100.0},
        50.0));
}

void Game::onUpdate(float deltaTime)
{
    for (int b_id:range(bubbles.size())){
        Bubble& b=bubbles[b_id];
        b.frame();
    }
}

void Game::onDraw()
{
    ClearBackground(RAYWHITE);

    for (int b_id:range(bubbles.size())){
        Bubble& b=bubbles[b_id];
        DrawCircleV(b.pos,b.r, MAROON);
    }

    DrawFPS(10, 10);
}
