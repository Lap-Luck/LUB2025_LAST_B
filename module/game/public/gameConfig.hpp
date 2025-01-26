#pragma once

class GameConfig
{
    public:
        bool debugDraw {false};
        PhysicsConfig physicsConfig {};

        float minimalCameraSpeed = 1.0f;
        std::string ObstacleOnHitSound = "default";

        void onSerialize(ISerialize* inSerialize)
        {
            inSerialize->propertyBool("debugDraw",debugDraw);
            inSerialize->propertyFloat("minimalCameraSpeed",minimalCameraSpeed);
            inSerialize->propertyFloat("minimalCameraSpeed",minimalCameraSpeed);

            inSerialize->propertyStruct("PhysicsConfig",[&](auto* ctx)
            {
                physicsConfig.onSerialize(ctx);
            });
        };
};