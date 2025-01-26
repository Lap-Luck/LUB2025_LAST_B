#pragma once

class GameConfig
{
    public:
        bool debugDraw {true};
        PhysicsConfig physicsConfig {};


        void onSerialize(ISerialize* inSerialize)
        {
            inSerialize->propertyBool("debugDraw",debugDraw);
            inSerialize->propertyStruct("PhysicsConfig",[&](auto* ctx)
            {
                physicsConfig.onSerialize(ctx);
            });
        };
};