#pragma once
#include "serialize.hpp"

enum{
  OLD,
  CALM,
    PHYSIC_ENGINE_COUNT
};

struct PhysicsConfig
{
   int type=OLD;
   int lerp_gravity=0.0f;

    void onSerialize(ISerialize* inSerialize)
    {
        inSerialize->propertyInt("type",type);
        inSerialize->propertyInt("lerp_gravity",lerp_gravity);
    };
};
