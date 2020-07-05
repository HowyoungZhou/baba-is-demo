#include "property.h"
#include "entity.h"

bool Property::on_collision(const Entity *source, Entity *target, TilePosition movement) const {
    auto nextEntities = Entity::get_entity_of_pos(target->get_tile_pos() + movement);
    if (!nextEntities) return true;
    bool res = true;
    for (auto nextEntity : *nextEntities) {
        if (!nextEntity->properties.top().on_collision(target, nextEntity, movement)) res = false;
    }
    return res;
}

bool MoveProperty::on_collision(const Entity *source, Entity *target, TilePosition movement) const {
    if (!Property::on_collision(source, target, movement)) return false;
    target->move_entity(target->get_tile_pos() + movement);
    return true;
}
