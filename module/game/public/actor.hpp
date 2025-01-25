#pragma once
#include "serialize.hpp"
#include "obstacle.hpp"
#include "vec2.hpp"

class GameState;

class Actor
{
public:
    virtual ~Actor() ;
    Actor(GameState& inGameState,Vec2f inPos) : state(inGameState), pos(inPos) {};

    virtual void onPlaced() = 0;
    virtual void onDraw() = 0;

    virtual void onSerialize(ISerialize* inSerialize)
    {
        inSerialize->propertyFloat("pos.x",pos.x);
        inSerialize->propertyFloat("pos.y",pos.y);
    };

    struct
    {
        bool pendingDestroy {false};
    } flags;


    Vec2f pos {};
    GameState& state;

    std::vector<CutLine::CutLineId> child_cutlines={};
    std::vector<Obstacle::ObstacleId> child_obstacles={};

    void SpawnnCutLine(CutLine cut ) ;
    void SpawnnObstacle(Obstacle cut ) ;

};


struct ActorFactoryEntry
{
    std::string className;
    std::function<std::unique_ptr<Actor>(class GameState&)> construct;
};


struct ActorFactory
{
    std::vector<ActorFactoryEntry> entries;
};