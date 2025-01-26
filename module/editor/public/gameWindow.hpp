#pragma once

#include <cmath>
#include <iostream>

#include "game.hpp"
#include "textureRenderer.hpp"
#include "window.hpp"
#include "gameState.hpp"
#include "raymath.h"

class GameWindow : public Window
{
    public:
        explicit GameWindow(Game inGame) : Window("GameWindow"), game(std::move(inGame)) {}

        void onInstanced() override
        {
            renderer.changeSize({
                1280,720
            });

            game.screenSize = Vec2i{1280,720};

            game.onInitialize();
        }

        void onResize(Vec2i oldSize, Vec2i newSize) override
        {
            renderer.changeSize(newSize);
            game.screenSize = newSize;
        }

        void closeRequested() override {pendingDestroy = true;};

        void onUpdate(float deltaTime) override
        {
            game.winPos = {renderer.lastRenderedScreenRect.x,renderer.lastRenderedScreenRect.y};
            if(focused)
            {
                if (IsKeyPressed(KEY_ESCAPE))
                    pendingDestroy = true;
                game.onUpdate(deltaTime);
            }

            renderer.drawContent([&]()
            {
                game.onDraw();
            });
        }

        void onImGuiDraw() override
        {
            renderer.draw();

        }

    protected:
        Game game;
        TextureRenderer renderer;
};