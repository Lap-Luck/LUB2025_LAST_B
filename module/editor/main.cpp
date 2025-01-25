#include <fstream>
#include <raylib.h>

#include "windowManager.hpp"
#include "gameState.hpp"
#include "editorWindow.hpp"
#include "game.hpp"
#include "gameWindow.hpp"

WindowManager*  WindowManager::instance = nullptr;
InputManager*   InputManager::instance = nullptr;

int main(void)
{
    GameState state {};
    Game game {state};

    WindowManager::get()->queueAddWindowView(std::make_unique<EditorWindow>(state));
    WindowManager::get()->queueAddWindowView(std::make_unique<GameWindow>(game));

    WindowManager::get()->properties.showImGuiShowcase    = false;
    WindowManager::get()->properties.showImGuiDebugInfo   = false;

    WindowManager::get()->run(
        Vec2i{1280,720},
        [&state]
        {
            ChangeDirectory("assets");
            state.assets.unknownTexture = LoadTexture("unknown.png");
        }
    );

    return 0;
}