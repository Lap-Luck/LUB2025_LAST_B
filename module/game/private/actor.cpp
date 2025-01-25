#include "gameState.hpp"

#include "actor.hpp"

  Actor::~Actor() {
    for (int cid:range(child_cutlines.size())) {
        auto cutId=child_cutlines[cid];
        state.cuts.getById(cutId)->flags.pendingDestroy = true;
    }
    for (int oid:range(child_obstacles.size())) {
        auto obstalceId=child_obstacles[oid];
        state.obstacles.getById(obstalceId)->flags.pendingDestroy = true;
    }
};


void Actor::SpawnnCutLine(CutLine cut ) {
    CutLine::CutLineId cutId = cut.unique_id;
    state.cuts.values.push_back(std::move(cut));
    child_cutlines.push_back(cutId);
};
void Actor::SpawnnObstacle(Obstacle cut ) {
    Obstacle::ObstacleId cutId = cut.unique_id;
    state.obstacles.values.push_back(std::move(cut));
    child_obstacles.push_back(cutId);
};
