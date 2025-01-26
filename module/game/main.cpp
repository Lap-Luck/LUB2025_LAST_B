#include <configSerializeHelpers.hpp>
#include <raylib.h>
#include "game.hpp"
#include "inputManager.hpp"
#include <string>
#include "actorSerializeHelpers.hpp"
#include "actor/registeredActors.hpp"

InputManager*   InputManager::instance = nullptr;

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1920, 720, "LubJam");
    InitAudioDevice();
    SetTargetFPS(60);

    ChangeDirectory("assets");


    GameState state{};
    Game game{state};

    state.assets.load();
    state.actorFactory = ConstructAssetFactorty();

    ConfigLoad("config",state);
    loadFromFile("menu",state);

    game.onInitialize();

    while (!WindowShouldClose())
    {
        game.screenSize = {GetScreenWidth(),GetScreenHeight()};
        game.onUpdate(0.0);
        BeginDrawing();

        game.onDraw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}