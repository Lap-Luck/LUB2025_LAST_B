#pragma once

#include <cmath>
#include <iostream>

#include "textureRenderer.hpp"
#include "window.hpp"
#include "gameState.hpp"
#include "raymath.h"

class EditorWindow : public Window
{
    public:
        explicit EditorWindow(GameState& inState) : Window("EditorWindow"), state(inState) {}

        void onInstanced() override
        {
            renderer.changeSize({
                std::min(size.x,size.y),
                std::min(size.x,size.y)
            });

            camera = { 0 };
            camera.target = (Vector2){ 0,0 };
            camera.offset = (Vector2){ 0,0 };
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;
        }

        void onResize(Vec2i oldSize, Vec2i newSize) override
        {
            renderer.changeSize(newSize);
        }

        void onUpdate(float deltaTime) override
        {
            Vec2f mousePos;
            mousePos.x = (GetMousePosition().x - renderer.lastRenderedScreenRect.x);
            mousePos.y = (GetMousePosition().y - renderer.lastRenderedScreenRect.y);
            Vector2 mouseWorldPos = GetScreenToWorld2D(Vector2(mousePos), camera);

            if(focused && mousePos.x > 0 && mousePos.y > 0 && mousePos.x < renderer.lastRenderedScreenRect.width && mousePos.y < renderer.lastRenderedScreenRect.height)
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                {
                    Vector2 delta = GetMouseDelta();
                    delta = Vector2Scale(delta, -1.0f/camera.zoom);
                    camera.target = Vector2Add(camera.target, delta);
                }
                float wheel = GetMouseWheelMove();

                if (wheel != 0)
                {
                    camera.offset = Vector2(mousePos);
                    camera.target = mouseWorldPos;
                    float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
                    if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
                    camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 64.0f);
                }
                camera.zoom += ((float)GetMouseWheelMove()*0.05f);
            }

            renderer.drawContent([&]()
            {
                BeginMode2D(camera);
                DrawTexture(state.assets.unknownTexture,0,0,WHITE);
                EndMode2D();
            });
        }

        void onImGuiDraw() override
        {
            renderer.draw();

        }

    protected:
        GameState& state;
        TextureRenderer renderer;
        Camera2D camera {0};
};