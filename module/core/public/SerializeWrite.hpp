#pragma once
#include <functional>
#include <iostream>
#include <string>

#include "serialize.hpp"
#include "thirdParty/rapidXml/rapidxml.hpp"

class SerializeWrite : public ISerialize
{
public:
    rapidxml::xml_document<>* root;
    rapidxml::xml_node<>* topNode;

    SerializeWrite(rapidxml::xml_document<>* inRoot, rapidxml::xml_node<>* inTopNode)
     : root(inRoot), topNode(inTopNode) {}

    void propertyStruct(std::string inName, std::function<void(ISerialize* inSerialize)> inInner) override
    {
        const auto* name = root->allocate_string(inName.c_str(),inName.size());

        rapidxml::xml_node<>* node = root->allocate_node(rapidxml::node_element, name,nullptr,inName.size(),0);
        topNode->append_node(node);

        SerializeWrite ctx {root,node};
        inInner(&ctx);
    }
    void propertyString(std::string inName, std::string& inValue) override
    {
        std::string valueStr = inValue;
        auto* name = root->allocate_string(inName.c_str(),inName.size());
        auto* value = root->allocate_string(valueStr.c_str(),valueStr.size());

        rapidxml::xml_node<>* node = root->allocate_node(rapidxml::node_element, name, value,inName.size(),valueStr.size());
        topNode->append_node(node);
    }

    void propertyFloat(std::string inName, float& inValue) override
    {
        std::string valueStr = std::to_string(inValue);
        auto* name = root->allocate_string(inName.c_str(),inName.size());
        auto* value = root->allocate_string(valueStr.c_str(),valueStr.size());

        rapidxml::xml_node<>* node = root->allocate_node(rapidxml::node_element, name, value,inName.size(),valueStr.size());
        topNode->append_node(node);
    }
    void propertyInt(std::string inName, int& inValue) override
    {
        std::string valueStr = std::to_string(inValue);
        auto* name = root->allocate_string(inName.c_str(),inName.size());
        auto* value = root->allocate_string(valueStr.c_str(),valueStr.size());

        rapidxml::xml_node<>* node = root->allocate_node(rapidxml::node_element, name, value,inName.size(),valueStr.size());
        topNode->append_node(node);
    }
    void propertyEnum(std::string inName, std::vector<std::string> options, std::string& selected) override
    {
        std::string valueStr = selected;
        auto* name = root->allocate_string(inName.c_str(),inName.size());
        auto* value = root->allocate_string(valueStr.c_str(),valueStr.size());

        rapidxml::xml_node<>* node = root->allocate_node(rapidxml::node_element, name, value,inName.size(),valueStr.size());
        topNode->append_node(node);
    }
};


class SerializeRead : public ISerialize
{
public:
    rapidxml::xml_document<>* root;
    rapidxml::xml_node<>* topNode;

    SerializeRead(rapidxml::xml_document<>* inRoot, rapidxml::xml_node<>* inTopNode)
     : root(inRoot), topNode(inTopNode) {}

    void propertyStruct(std::string inName, std::function<void(ISerialize* inSerialize)> inInner) override
    {
        rapidxml::xml_node<>* node = topNode->first_node(inName.c_str());
        if(!node) { std::cout << "[WRN] Couldn't read "<<inName<<"\n";  return;};
        SerializeRead ctx = {root,node};
        inInner(&ctx);
    }

    void propertyListStruct(std::string inName, std::function<void(ISerialize* inSerialize)> inInner) override
    {
        for(rapidxml::xml_node<>* node = topNode->first_node(inName.c_str()); node != nullptr; node = node->next_sibling(inName.c_str()))
        {
            SerializeRead ctx = {root,node};
            inInner(&ctx);
        }
    }

    void propertyString(std::string inName, std::string& inValue) override
    {
        rapidxml::xml_node<>* node = topNode->first_node(inName.c_str());
        if(node) inValue = node->value();
        else std::cout << "[WRN] Couldn't read "<<inName<<"\n";
    }

    void propertyFloat(std::string inName, float& inValue) override
    {
        rapidxml::xml_node<>* node = topNode->first_node(inName.c_str());
        if(node) inValue = std::stof(node->value());
        else std::cout << "[WRN] Couldn't read "<<inName<<"\n";
    }
    void propertyInt(std::string inName, int& inValue) override
    {
        rapidxml::xml_node<>* node = topNode->first_node(inName.c_str());
        if(node) inValue = std::stoi(node->value());
        else std::cout << "[WRN] Couldn't read "<<inName<<"\n";
    }
    void propertyEnum(std::string inName, std::vector<std::string> options, std::string& selected) override
    {
        rapidxml::xml_node<>* node = topNode->first_node(inName.c_str());
        if(node) selected = node->value();
        else std::cout << "[WRN] Couldn't read "<<inName<<"\n";
    }
};
