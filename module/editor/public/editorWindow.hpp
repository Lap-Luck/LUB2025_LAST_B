#pragma once

#include <actorSerializeHelpers.hpp>
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

            bool capturedInput {false};
            float wheel = GetMouseWheelMove();
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
                        edState.selectedActor =state.actors.values[state.actors.values.size()-1];

                        capturedInput = true;
                    }
                }
                else
                {
                    if (IsKeyPressed(KEY_D) && !edState.selectedActor.expired())
                    {
                        auto actor = duplicateActor(edState.selectedActor.lock().get(),state);
                        actor->pos = mouseWorldPos;

                        state.actors.values.push_back(std::move(actor));
                        edState.selectedActor = state.actors.values[state.actors.values.size()-1];
                        capturedInput = true;
                    }
                }

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    edState.draggingActor = {};
                }

                if (!capturedInput)
                {
                    for (auto& it : state.actors.values)
                    {
                        Vec2f inWorld = it->pos;

                        Vec2f dist = inWorld - Vec2f(mouseWorldPos);
                        float distance = sqrt( (dist.x*dist.x) + (dist.y*dist.y) );
                        if ( distance < 20/camera.zoom)
                        {
                            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                            {
                                edState.draggingActor = it;
                                edState.selectedActor = it;
                            }

                            if (IsKeyDown(KEY_R))
                            {
                                if (wheel != 0)
                                {
                                    if(auto casted = std::dynamic_pointer_cast<IActorModifyParam>(it))
                                    {
                                        casted->requestChangeRotation(wheel*15);
                                    }
                                }
                            }
                            else
                            {
                                if (wheel != 0)
                                {
                                    if(auto casted = std::dynamic_pointer_cast<IActorModifyParam>(it))
                                    {
                                        casted->requestChangeScale(wheel/5.0);
                                    }
                                }
                            }

                            capturedInput = true;
                        }
                    }
                }

                if (!capturedInput)
                {
                    if (wheel != 0)
                    {
                        camera.offset = Vector2(mousePos);
                        camera.target = mouseWorldPos;
                        float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
                        if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
                        camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 64.0f);
                    }
                }
            }

            renderer.drawContent([&]()
            {
                BeginMode2D(camera);

                for (auto& it : state.actors.values)
                {
                    it->onDraw();
                }
                for (auto& it : state.actors.values)
                {
                    DrawCircle(it->pos.x,it->pos.y,20/camera.zoom,PINK);
                }

                DrawRectangleLines(-1440/2,-2000,1440,2000,BLACK);

                DrawCircle(0,0,20/camera.zoom,BLUE);
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