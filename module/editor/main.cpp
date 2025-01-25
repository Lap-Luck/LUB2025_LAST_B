#include <fstream>
#include <raylib.h>

#include "windowManager.hpp"
#include "gameState.hpp"
#include "editorWindow.hpp"
#include "game.hpp"
#include "gameWindow.hpp"
#include "selectionWindow.hpp"
#include "serializeFile.hpp"
#include "actor/registeredActors.hpp"

#include "thirdParty/rapidXml/rapidxml.hpp"
#include <thirdParty/rapidXml/rapidxml_print.hpp>
#include <thirdParty/rapidXml/rapidxml_utils.hpp>

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
            SetExitKey(KEY_F12);

            SetTargetFPS(60);
            ChangeDirectory("assets");
            state.assets.load();
        }
    );

    rapidxml::xml_document<> root {};
    rapidxml::xml_node<> *node = root.allocate_node(rapidxml::node_element, "all", nullptr );
    root.append_node(node);


    SerializeFile serializer{&root,node};


    for (auto& it : state.actors.values)
    {
        serializer.propertyStruct("actor",[&](auto* structSerializer)
        {
            std::string temp = it->getClassName();
            structSerializer->propertyString("TYPE",temp);
            it->onSerialize(structSerializer);
        });
    }


    std::ofstream out("state.xml");
    out << root;
    root.clear();

    return 0;
}