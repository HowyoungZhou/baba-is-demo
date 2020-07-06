#include "level_controller.h"
#include "entity.h"

LevelController *LevelController::instance = nullptr;

void LevelController::move_entities(Vector2<long> movement) {
    auto comp = [movement](const Entity *e1, const Entity *e2) {
        return e1->get_tile_pos().dot(movement) > e2->get_tile_pos().dot(movement);
    };
    std::vector<Entity *> sortedEntities(controlledEntities.cbegin(), controlledEntities.cend());
    std::sort(sortedEntities.begin(), sortedEntities.end(), comp);
    for (auto entity : sortedEntities) {
        move_property.on_collision(nullptr, entity, movement);
    }
}
