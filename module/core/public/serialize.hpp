#pragma once
#include <functional>

class ISerialize
{
public:
    virtual ~ISerialize() = default;

    virtual void propertyStruct(std::string inName, std::function<void(ISerialize* inSerialize)> inInner) = 0;
    virtual void propertyFloat(std::string inName, float& inValue) = 0;
    virtual void propertyInt(std::string inName, int& inValue) = 0;
    virtual void propertyEnum(std::string inName, std::vector<std::string> options, std::string& selected) = 0;

};