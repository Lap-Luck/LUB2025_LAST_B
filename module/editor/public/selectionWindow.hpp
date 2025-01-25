#pragma once

#include <cmath>
#include <iostream>

#include "editorState.hpp"
#include "gameState.hpp"
#include "serialize.hpp"
#include "window.hpp"
#include "serializePreview.hpp"

class SelectionWindow : public Window
{
public:
    explicit SelectionWindow(GameState& inGame,EditorState& inEdState) : Window("SelectionWindow"), state(inGame), edState(inEdState) {}



    void onInstanced() override
    {

    }

    void onUpdate(float deltaTime) override
    {

    }

    void onImGuiDraw() override
    {
        if(ImGui::Button("Start"))
        {
            Game game {state};
            game.onInitialize();
            WindowManager::get()->queueAddWindowView(std::make_unique<GameWindow>(game));
        }
        ImGui::Separator();
        std::vector<const char*> items;
        for (auto& it : state.actorFactory.entries)
        {
            items.push_back(it.className.c_str());
        }

        ImGui::Combo("Actor to", &edState.selectedActorFactoryEntry, items.data(), items.size()); ImGui::SameLine();
        if(ImGui::Button("Add"))
        {
            edState.toPlace = state.actorFactory.entries[edState.selectedActorFactoryEntry].construct(state);
        }
        ImGui::Separator();

        if (!edState.selectedActor.expired())
        {
            SerializePreview preview;
            edState.selectedActor.lock()->onSerialize(&preview);

            if(ImGui::Button("RemoveActor"))
            {
                std::erase_if(state.actors.values,[&](auto& in) { return in.get() == edState.selectedActor.lock().get(); });
            }
        }


    }

protected:
    GameState& state;
    EditorState& edState;

};
