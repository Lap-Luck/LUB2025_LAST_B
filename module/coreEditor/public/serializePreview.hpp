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

    void propertyFloat(std::string inName, float& inValue) override
    {
        float temp = inValue;
        ImGui::InputFloat(inName.c_str(),&temp);
        if(temp != inValue)
            inValue = temp;
    }
};