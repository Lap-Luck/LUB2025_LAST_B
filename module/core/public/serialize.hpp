#pragma once
#include <functional>

class ISerialize
{
public:
    virtual ~ISerialize() = default;

    virtual void propertyStruct(std::string inName, std::function<void(ISerialize* inSerialize)> inInner) = 0;
    virtual void propertyFloat(std::string inName, float& inValue) = 0;
};