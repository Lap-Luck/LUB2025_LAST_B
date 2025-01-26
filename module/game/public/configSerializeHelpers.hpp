#pragma once

#include <gameState.hpp>

#include "thirdParty/rapidXml/rapidxml.hpp"
#include <thirdParty/rapidXml/rapidxml_print.hpp>
#include <thirdParty/rapidXml/rapidxml_utils.hpp>

#include "SerializeWrite.hpp"

inline void ConfigSave(std::string name, GameState& state)
{
    rapidxml::xml_document<> root {};
    rapidxml::xml_node<> *node = root.allocate_node(rapidxml::node_element, "config", nullptr );
    root.append_node(node);

    SerializeWrite serializer{&root,node};
    state.config.onSerialize(&serializer,state);


    std::ofstream out(name+".xml");
    out << root;
    root.clear();
}

inline void ConfigLoad(std::string name, GameState& state)
{
    state.actors.values.clear();

    rapidxml::file<> in((name+".xml").c_str());
    rapidxml::xml_document<> root;
    root.parse<0>(in.data());
    SerializeRead reader{&root,&root};

    reader.propertyStruct("config",[&](ISerialize* ctx)
    {
        state.config.onSerialize(ctx,state);
    });

    root.clear();
}