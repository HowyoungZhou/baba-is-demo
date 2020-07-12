#include "level_controller.h"
#include "entity.h"
#include "text_entity.h"

LevelController *LevelController::instance = nullptr;

void LevelController::_ready() {
    TextEntity::rule_check();
}

void LevelController::move_entities(Vector2<long> movement) {
    auto comp = [movement](const Entity *e1, const Entity *e2) {
        return e1->get_tile_pos().dot(movement) > e2->get_tile_pos().dot(movement);
    };
    std::vector<Entity *> sortedEntities;
    // evaluate conditions of the YOU property
    for (auto entity : controlled_entities) {
        auto range = entity->properties.get_properties_of_type(Properties::YOU);
        auto res = true;
        for (auto iter = range.first; iter != range.second; ++iter) {
            if (iter->second->enabled(entity)) continue;
            res = false;
            break;
        }
        if (res) sortedEntities.push_back(entity);
    }
    // move the front entities in the direction of the movement first
    std::sort(sortedEntities.begin(), sortedEntities.end(), comp);

    for (auto entity : sortedEntities) {
        PushProperty().on_collision(nullptr, entity, movement);
    }
}
