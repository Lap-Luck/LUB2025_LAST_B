#pragma once
#include "serialize.hpp"

class SerializePreview : public ISerialize
{
public:
    void propertyStruct(std::string inName, std::function<void(ISerialize* inSerialize)> inInner) override
    {
        if (ImGui::TreeNode(inName.c_str()))
        {
            inInner(this);
            ImGui::TreePop();
        }
    }

    void propertyString(std::string inName, std::string& inValue) override
    {
        char buffor[1024];
        strncpy(buffor,inValue.c_str(),1024);
        ImGui::InputText(inName.c_str(),buffor,1024);
        inValue = buffor;
    }

    void propertyBool(std::string inName, bool& inValue) override
    {
        ImGui::Checkbox(inName.c_str(),&inValue);
    }

    void propertyFloat(std::string inName, float& inValue) override
    {
        float temp = inValue;
        ImGui::InputFloat(inName.c_str(),&temp);
        if(temp != inValue)
            inValue = temp;
    }

    void propertyInt(std::string inName, int& inValue) override
    {
        float temp = inValue;
        ImGui::InputFloat(inName.c_str(),&temp);
        if(temp != inValue)
            inValue = temp;
    }

    void propertyEnum(std::string inName, std::vector<std::string> options, std::string& selected) override
    {
        std::vector<const char*> items;
        int i = 0;
        int sel = 0;
        for (auto& it : options)
        {
            if (selected == it) sel = i;
            items.push_back(it.c_str());
            i++;
        }

        ImGui::Combo(inName.c_str(), &sel, items.data(), items.size());
        selected = options[sel];
    }
};