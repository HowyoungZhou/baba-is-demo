#ifndef BABA_IS_YOU_LEVEL_CONTROLLER_H
#define BABA_IS_YOU_LEVEL_CONTROLLER_H

#include "vector2.h"
#include "words.h"

#include <Godot.hpp>
#include <Node2D.hpp>
#include <InputEvent.hpp>

#include <unordered_set>
#include <map>

class Entity;

class LevelController : public godot::Node2D {
GODOT_CLASS(LevelController, godot::Node2D);
public:
    static LevelController *instance;
    std::unordered_set<Entity*> controlled_entities;

    static void _register_methods() {
        godot::register_method("_enter_tree", &LevelController::_enter_tree);
        godot::register_method("_exit_tree", &LevelController::_exit_tree);
        godot::register_method("_unhandled_input", &LevelController::_unhandled_input);
        godot::register_method("_ready", &LevelController::_ready);

        godot::register_property<LevelController, real_t>("tileSize", &LevelController::set_tile_size,
                                                          &LevelController::get_tile_size, 24.f);
    }

    void _init() {}

    void _ready();

    void _enter_tree() {
        instance = this;
    }

    void _exit_tree() {
        instance = nullptr;
    }

    void _unhandled_input(const godot::Ref<godot::InputEvent> event) {
        if (event->is_action_pressed("ui_up")) move_entities(Vector2<long>(0, -1), Directions::UP);
        else if (event->is_action_pressed("ui_down")) move_entities(Vector2<long>(0, 1), Directions::DOWN);
        else if (event->is_action_pressed("ui_left")) move_entities(Vector2<long>(-1, 0), Directions::LEFT);
        else if (event->is_action_pressed("ui_right")) move_entities(Vector2<long>(1, 0), Directions::RIGHT);
    }

    real_t get_tile_size() const {
        return tileSize;
    }

    void set_tile_size(real_t value) {
        tileSize = value;
    }

    Vector2<long> get_tile_dim() {
        auto size = get_viewport_rect().get_size() / tileSize;
        return Vector2<long>(std::ceil(size.x), std::ceil(size.y));
    }

    void set_tile_dim(Vector2<long> dim) {
        get_viewport_rect().set_size(static_cast<godot::Vector2>(dim * get_tile_size()));
    }

    void add_controlled_entity(Entity *entity) { controlled_entities.insert(entity); }

private:
    real_t tileSize = 24.f;

    void move_entities(Vector2<long> movement, Directions direction);
};

#endif //BABA_IS_YOU_LEVEL_CONTROLLER_H
