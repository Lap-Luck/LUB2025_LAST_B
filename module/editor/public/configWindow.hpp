#pragma once

#include <actorSerializeHelpers.hpp>
#include <cmath>
#include <iostream>

#include "editorState.hpp"
#include "gameState.hpp"
#include "serialize.hpp"
#include "window.hpp"
#include "serializePreview.hpp"

class ConfigWindow : public Window
{
public:
    explicit ConfigWindow(GameState& inGame,EditorState& inEdState) : Window("ConfigWindow"), state(inGame), edState(inEdState) {}


    void onInstanced() override
    {

    }

    void onUpdate(float deltaTime) override
    {

    }

    void onImGuiDraw() override
    {
        SerializePreview preview;

        ImGui::LabelText("Global","Global");
        state.config.onSerialize(&preview);
        ImGui::Separator();
        ImGui::LabelText("Level","Level");
        state.levelConfig.onSerialize(&preview);

    }

protected:
    GameState& state;
    EditorState& edState;
};
