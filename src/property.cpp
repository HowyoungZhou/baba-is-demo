#include "property.h"
#include "entity.h"

bool Property::on_collision(Entity *source, Entity *target, TilePosition movement) const {
    auto range = Entity::get_entities_at_pos(target->get_tile_pos() + movement);
    std::vector<Entity *> next_entities;
    for (auto iter = range.first; iter != range.second; ++iter) next_entities.push_back(iter->second);

    auto res = true;
    for (auto entity : next_entities) {
        if (!entity->properties.on_collision(target, entity, movement)) res = false;
    }
    return res;
}

bool PushProperty::on_collision(Entity *source, Entity *target, TilePosition movement) const {
    if (!Property::on_collision(source, target, movement)) return false;
    target->set_tile_pos(target->get_tile_pos() + movement);
    return true;
}

bool DefeatProperty::on_collision(Entity *source, Entity *target, TilePosition movement) const {
	if (source->properties.has_property(Properties::SINK)) {
		target->destroy();
		source->destroy();
		return true;
	}
    if (source->properties.has_property(Properties::YOU)) source->destroy();
    return true;
}

// added by zdz 20.07.16
bool SinkProperty::on_collision(Entity *source, Entity *target, TilePosition movement) const {
	if (target->properties.has_property(Properties::PUSH)) {
		if (!Property::on_collision(source, target, movement)) return false;
		target->set_tile_pos(target->get_tile_pos() + movement);
		return true;
	}
    // target destroyed
    target->destroy();
    source->destroy();
    return true;
}

bool HotProperty::on_collision(Entity *source, Entity *target, TilePosition movement) const {
	if (target->properties.has_property(Properties::PUSH)) {
		if (!Property::on_collision(source, target, movement)) return false;
		target->set_tile_pos(target->get_tile_pos() + movement);
		return true;
	}
    if (source->properties.has_property(Properties::MELT)) source->destroy();
    return true;
}

bool WinProperty::on_collision(Entity *source, Entity *target, TilePosition movement) const {
    // TODO: stage win: change scene, need operate outside
    return true;
}

bool ShutProperty::on_collision(Entity *source, Entity *target, TilePosition movement) const {
    if (!source->properties.has_property(Properties::OPEN)) return false;//STOP
    source->destroy();
    target->destroy();
    return true;
}
