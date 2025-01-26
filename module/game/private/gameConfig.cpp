#include "gameConfig.hpp"

#include <gameState.hpp>

#include "serialize.hpp"

void GameConfig::onSerialize(ISerialize* inSerialize,class GameState& state)
{
    inSerialize->propertyBool("debugDraw",debugDraw);
    inSerialize->propertyFloat("minimalCameraSpeed",minimalCameraSpeed);

    inSerialize->propertyStruct("Sound",[&](auto* ctx)
    {
        inSerialize->propertyEnum("ObstacleOnHitSound",state.assets.soundKeys,ObstacleOnHitSound);
        inSerialize->propertyFloat("ObstacleOnHitVolume",ObstacleOnHitVolume);
    });

    inSerialize->propertyStruct("PhysicsConfig",[&](auto* ctx)
    {
        physicsConfig.onSerialize(ctx);
    });
};