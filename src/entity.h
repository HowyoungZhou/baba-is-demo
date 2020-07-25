#ifndef BABA_IS_YOU_ENTITY_H
#define BABA_IS_YOU_ENTITY_H

#include "words.h"
#include "property.h"
#include "level_controller.h"
#include "vector2.h"

#include <Godot.hpp>
#include <AnimatedSprite.hpp>
#include <Tween.hpp>
#include <nativescript/godot_nativescript.h>

#include <queue>
#include <set>

class Entity : public godot::AnimatedSprite {
GODOT_CLASS(Entity, AnimatedSprite)
public:
    PropertyList properties;

    static void _register_methods() {
        godot::register_method("_ready", &Entity::_ready);
        godot::register_method("_enter_tree", &Entity::_enter_tree);
        godot::register_method("_exit_tree", &Entity::_exit_tree);

        godot::register_property<Entity, size_t>("Noun", &Entity::noun, 0,
                                                 GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                                                 GODOT_PROPERTY_HINT_ENUM, kNounsHintString);
    }

    void _init() {}

    void _ready() {
        tween = godot::Tween::_new();
        add_child(tween);
    }

    Nouns get_noun() const {
        return static_cast<Nouns>(noun + static_cast<size_t>(Nouns::ALGAE));
    }

    void set_noun(Nouns value) {
        noun = static_cast<size_t>(value) - static_cast<size_t>(Nouns::ALGAE);
    }

    TilePosition get_tile_pos() const {
        return tile_pos_;
    }

    void _enter_tree() {
        update_tile_pos();
        register_entity();
    }

    void _exit_tree() {
        unregister_entity();
        LevelController::instance->controlled_entities.erase(this);
        if (LevelController::instance->controlled_entities.empty()) {
            LevelController::instance->show_lose_screen();
        }
    }

    void set_position(const godot::Vector2 value) {
        godot::Node2D::set_position(value);
        update_tile_pos();
    }

    void register_entity() {
        nounEntityMap.insert({get_noun(), this});
        posEntityMap.insert({get_tile_pos(), this});
    }

    void unregister_entity() {
        erase_pair(nounEntityMap, get_noun(), this);
        erase_pair(posEntityMap, get_tile_pos(), this);
    }

    virtual void set_tile_pos(TilePosition newPos) {
        unregister_entity();
        tile_pos_ = newPos;
        register_entity();

        auto tileSize = get_tile_size();
        auto pos = static_cast<godot::Vector2>(newPos) * tileSize + 0.5f * godot::Vector2(tileSize, tileSize);
        tween->interpolate_property(this, "position", get_position(), pos, 1.0 / speed, godot::Tween::TRANS_QUAD,
                                    godot::Tween::EASE_IN_OUT);
        tween->start();
    }

    static auto get_entities_at_pos(TilePosition pos) {
        return posEntityMap.equal_range(pos);
    }

    static auto find_entities_of_noun(Nouns noun) {
        return nounEntityMap.equal_range(noun);
    }

    void destroy() {
        queue_free();
        properties.on_destroyed(this);
    }

protected:
    const real_t speed = 4;

    size_t noun = 0;
    TilePosition tile_pos_;
    godot::Tween *tween;

    static std::unordered_multimap<Nouns, Entity *> nounEntityMap;
    static std::unordered_multimap<TilePosition, Entity *> posEntityMap;

    static real_t get_tile_size() {
        return LevelController::instance->get_tile_size();
    }

    template<class Map>
    static void erase_pair(Map &map, typename Map::key_type key, typename Map::mapped_type value) {
        for (auto iter = map.equal_range(key); iter.first != iter.second; ++iter.first) {
            if (!(iter.first->second == value)) continue;
            map.erase(iter.first);
            return;
        }
    }

    virtual void update_tile_pos() {
        auto tileSize = get_tile_size();
        auto tilePos = (get_position() - 0.5f * godot::Vector2(tileSize, tileSize)) / tileSize;
        tile_pos_ = TilePosition(std::lround(tilePos.x), std::lround(tilePos.y));
    }
};

#endif //BABA_IS_YOU_ENTITY_H
