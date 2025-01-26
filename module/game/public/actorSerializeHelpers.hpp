#pragma once

#include <gameState.hpp>

#include "thirdParty/rapidXml/rapidxml.hpp"
#include <thirdParty/rapidXml/rapidxml_print.hpp>
#include <thirdParty/rapidXml/rapidxml_utils.hpp>

#include "SerializeWrite.hpp"

inline void saveToFile(std::string name, GameState& state)
{
    rapidxml::xml_document<> root {};
    rapidxml::xml_node<> *node = root.allocate_node(rapidxml::node_element, "state", nullptr );
    root.append_node(node);


    SerializeWrite serializer{&root,node};


    for (auto& it : state.actors.values)
    {
        serializer.propertyStruct("actor",[&](auto* structSerializer)
        {
            std::string temp = it->getClassName();
            structSerializer->propertyString("TYPE",temp);
            it->onSerialize(structSerializer);
        });
    }


    std::ofstream out("levels/"+name+".xml");
    out << root;
    root.clear();
}

inline void loadFromFile(std::string name, GameState& state)
{
    state.actors.values.clear();

    rapidxml::file<> in(("levels/"+name+".xml").c_str());
    rapidxml::xml_document<> root;
    root.parse<0>(in.data());
    SerializeRead reader{&root,&root};

    reader.propertyStruct("state",[&](ISerialize* ctx)
    {
        ctx->propertyListStruct("actor",[&](ISerialize* actorCtx)
        {
            std::string typeName;
            actorCtx->propertyString("TYPE",typeName);

            auto* entry = state.actorFactory.getByClassName(typeName);
            if(!entry) return;

            auto actor = entry->construct(state);
            actor->onSerialize(actorCtx);
            state.actors.values.push_back(std::move(actor));
        });
    });

    root.clear();
}

inline std::unique_ptr<Actor> duplicateActor(Actor* actor, GameState& state)
{
    rapidxml::xml_document<> root {};
    rapidxml::xml_node<> *node = root.allocate_node(rapidxml::node_element, "state", nullptr );
    root.append_node(node);

    SerializeWrite serializer{&root,node};
    actor->onSerialize(&serializer);

    auto fac = state.actorFactory.getByClassName(actor->getClassName());
    if (!fac) return {};

    std::unique_ptr<Actor> out = fac->construct(state);

    SerializeRead reader{&root,node};
    out->onSerialize(&reader);
    root.clear();

    return out;

}