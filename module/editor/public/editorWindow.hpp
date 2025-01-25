#pragma once

#include <cmath>
#include <iostream>

#include "editorState.hpp"
#include "textureRenderer.hpp"
#include "window.hpp"
#include "gameState.hpp"
#include "raymath.h"

class EditorWindow : public Window
{
    public:
        explicit EditorWindow(GameState& inState,EditorState& inEdState) : Window("EditorWindow"), state(inState), edState(inEdState) {}

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

            if(mousePos.x > 0 && mousePos.y > 0 && mousePos.x < renderer.lastRenderedScreenRect.width && mousePos.y < renderer.lastRenderedScreenRect.height)
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                {
                    Vector2 delta = GetMouseDelta();
                    delta = Vector2Scale(delta, -1.0f/camera.zoom);
                    camera.target = Vector2Add(camera.target, delta);
                }

                if(!edState.draggingActor.expired())
                {
                    Vector2 delta = GetMouseDelta();
                    delta = Vector2Scale(delta, -1.0f/camera.zoom);
                    edState.draggingActor.lock()->pos -= delta;
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if(edState.toPlace)
                    {
                        edState.toPlace->pos = mouseWorldPos;
                        state.actors.values.push_back(std::move(edState.toPlace));
                    }
                    for (auto& it : state.actors.values)
                    {
                        Vec2f inWorld = it->pos;
                        std::cout << inWorld.x << " " << inWorld.y << " | " << mouseWorldPos.y << " " << mouseWorldPos.y << std::endl;
                        if (mouseWorldPos.x > inWorld.x && mouseWorldPos.x < inWorld.x+20
                            &&  mouseWorldPos.y > inWorld.y && mouseWorldPos.y < inWorld.y+20)
                        {
                            edState.draggingActor = it;
                            edState.selectedActor = it;
                        }
                    }
                }

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    edState.draggingActor = {};
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

                DrawCircle(0,0,20,BLUE);

                for (auto& it : state.actors.values)
                {
                    it->onDraw();
                }
                for (auto& it : state.actors.values)
                {
                    DrawRectangle(it->pos.x,it->pos.y,20,20,RED);
                }
                EndMode2D();
            });
        }

        void onImGuiDraw() override
        {
            renderer.draw();

        }

    protected:
        GameState& state;
        EditorState& edState;
        TextureRenderer renderer;
        Camera2D camera {0};
};