#pragma once
#include <physicConfig.hpp>
#include <string>

class GameConfig
{
    public:
        bool debugDraw {false};
        PhysicsConfig physicsConfig {};

        float minimalCameraSpeed = 1.0f;
        std::string ObstacleOnHitSound = "default";
        float ObstacleOnHitVolume = 1.0f;

        void onSerialize(ISerialize* inSerialize,class GameState& state);
};
