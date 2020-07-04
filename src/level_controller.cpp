#include "level_controller.h"

LevelController *LevelController::instance = nullptr;

void LevelController::register_entity(Entity *entity) {
    instance->nounEntityMap[entity->get_noun()].insert(entity);
    instance->posEntityMap[getTilePos(entity)].insert(entity);
}

void LevelController::unregister_entity(Entity *entity) {
    instance->nounEntityMap[entity->get_noun()].erase(entity);
    instance->posEntityMap[getTilePos(entity)].erase(entity);
}

std::pair<long, long> LevelController::getTilePos(const Entity *entity) const {
    auto tilePos = (entity->get_position() - 0.5 * godot::Vector2(tileSize, tileSize)) / tileSize;
    return std::make_pair(std::lround(tilePos.x), std::lround(tilePos.y));
}
