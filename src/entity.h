#ifndef BABA_IS_YOU_ENTITY_H
#define BABA_IS_YOU_ENTITY_H

#include "enums.h"
#include "property.h"
#include "level_controller.h"
#include "vector2.h"

#include <Godot.hpp>
#include <Sprite.hpp>
#include <nativescript/godot_nativescript.h>

#include <queue>

struct PropertyPriorityComparer {
    bool operator()(const Property &prop1, const Property &prop2) const {
        return prop1.get_priority() < prop2.get_priority();
    }
};

class Entity : public godot::Sprite {
GODOT_CLASS(Entity, Sprite);
public:
    std::priority_queue<Property, std::vector<Property>, PropertyPriorityComparer> properties;

    static void _register_methods() {
        godot::register_method("_enter_tree", &Entity::_enter_tree);
        godot::register_method("_exit_tree", &Entity::_exit_tree);
        godot::register_property<Entity, size_t>("Noun", &Entity::noun, BABA,
                                                 GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                                                 GODOT_PROPERTY_HINT_ENUM, NounHintString);
    }

    void _init() {}

    Noun get_noun() const { return static_cast<Noun>(noun); };

    void set_noun(Noun value) { noun = value; }

    TilePosition get_tile_pos() const {
        auto tileSize = get_tile_size();
        auto tilePos = (get_position() - 0.5 * godot::Vector2(tileSize, tileSize)) / tileSize;
        return TilePosition(std::lround(tilePos.x), std::lround(tilePos.y));
    }

    void _enter_tree() { register_entity(); }

    void _exit_tree() { unregister_entity(); }

    void register_entity() {
        nounEntityMap[get_noun()].insert(this);
        posEntityMap[get_tile_pos()].insert(this);
    }

    void unregister_entity() {
        nounEntityMap[get_noun()].erase(this);
        posEntityMap[get_tile_pos()].erase(this);
    }

    void move_entity(TilePosition newPos) {
        unregister_entity();
        auto tileSize = get_tile_size();
        auto pos = static_cast<godot::Vector2>(newPos) * tileSize + 0.5 * godot::Vector2(tileSize, tileSize);
        set_position(pos);
        register_entity();
    }

    static const std::unordered_set<Entity *> *get_entity_of_pos(TilePosition pos) {
        auto iter = posEntityMap.find(pos);
        if (iter == posEntityMap.cend()) return nullptr;
        return &iter->second;
    }

private:
    size_t noun;

    static std::unordered_map<Noun, std::unordered_set<Entity *>> nounEntityMap;
    static std::unordered_map<TilePosition, std::unordered_set<Entity *>, HashVector2> posEntityMap;

    static real_t get_tile_size() {
        return LevelController::instance->get_tile_size();
    }
};

#endif //BABA_IS_YOU_ENTITY_H
