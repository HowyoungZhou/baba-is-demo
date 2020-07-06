#include "property.h"
#include "entity.h"

Property property;
MoveProperty move_property;
StopProperty stop_property;

bool Property::on_collision(const Entity *source, Entity *target, TilePosition movement) const {
    std::vector<Entity *> nextEntities;
    Entity::get_entities_at_pos(target->get_tile_pos() + movement, std::back_inserter(nextEntities));
    if (nextEntities.empty()) return true;
    auto res = true;
    for (auto nextEntity : nextEntities) {
        if (nextEntity->properties.empty()) continue;
        if (!nextEntity->properties.top()->on_collision(target, nextEntity, movement)) res = false;
    }
    return res;
}

bool MoveProperty::on_collision(const Entity *source, Entity *target, TilePosition movement) const {
    if (!Property::on_collision(source, target, movement)) return false;
    target->move_entity(target->get_tile_pos() + movement);
    return true;
}
