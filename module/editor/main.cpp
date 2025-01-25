#include <fstream>
#include <raylib.h>

#include "windowManager.hpp"
#include "gameState.hpp"
#include "editorWindow.hpp"
#include "game.hpp"
#include "gameWindow.hpp"
#include "selectionWindow.hpp"
#include "actor/registeredActors.hpp"

WindowManager*  WindowManager::instance = nullptr;
InputManager*   InputManager::instance = nullptr;

int main(void)
{
    GameState state {};
    EditorState edState {};
    Game game {state};
    state.actorFactory = ConstructAssetFactorty();

    WindowManager::get()->queueAddWindowView(std::make_unique<EditorWindow>(state,edState));
    //WindowManager::get()->queueAddWindowView(std::make_unique<GameWindow>(game));
    WindowManager::get()->queueAddWindowView(std::make_unique<SelectionWindow>(state,edState));

    WindowManager::get()->properties.showImGuiShowcase    = false;
    WindowManager::get()->properties.showImGuiDebugInfo   = false;

    WindowManager::get()->run(
        Vec2i{1280,720},
        [&state]
        {
            SetTargetFPS(60);
            ChangeDirectory("assets");
            state.assets.load();
        }
    );

    return 0;
}