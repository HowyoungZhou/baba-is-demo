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
    std::vector<Entity *> sortedEntities(controlled_entities.cbegin(), controlled_entities.cend());
    std::sort(sortedEntities.begin(), sortedEntities.end(), comp);
    for (auto entity : sortedEntities) {
        PushProperty().on_collision(nullptr, entity, movement);
    }
}
