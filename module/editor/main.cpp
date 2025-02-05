#include <fstream>
#include <raylib.h>

#include "configWindow.hpp"
#include "windowManager.hpp"
#include "gameState.hpp"
#include "editorWindow.hpp"
#include "game.hpp"
#include "gameWindow.hpp"
#include "selectionWindow.hpp"
#include "SerializeWrite.hpp"
#include "actor/registeredActors.hpp"
#include "configSerializeHelpers.hpp"

WindowManager*  WindowManager::instance = nullptr;
InputManager*   InputManager::instance = nullptr;

int main(void)
{
    InitAudioDevice();

    GameState state {};
    EditorState edState {};
    Game game {state};

    ChangeDirectory("assets");

    state.actorFactory = ConstructAssetFactorty();
    ConfigLoad("config",state);

    WindowManager::get()->queueAddWindowView(std::make_unique<EditorWindow>(state,edState));
    //WindowManager::get()->queueAddWindowView(std::make_unique<GameWindow>(game));
    WindowManager::get()->queueAddWindowView(std::make_unique<SelectionWindow>(state,edState));
    WindowManager::get()->queueAddWindowView(std::make_unique<ConfigWindow>(state,edState));

    WindowManager::get()->properties.showImGuiShowcase    = false;
    WindowManager::get()->properties.showImGuiDebugInfo   = false;

    WindowManager::get()->run(
        Vec2i{1280,720},
        [&state]
        {
            SetExitKey(KEY_F12);

            SetTargetFPS(60);
            state.assets.load();
            loadFromFile("default",state);
        }
    );
    CloseAudioDevice();
    ConfigSave("config",state);

    return 0;
}