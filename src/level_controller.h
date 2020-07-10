#ifndef BABA_IS_YOU_LEVEL_CONTROLLER_H
#define BABA_IS_YOU_LEVEL_CONTROLLER_H

#include "vector2.h"

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
    std::unordered_set<Entity*> controlledEntities;

    static void _register_methods() {
        godot::register_method("_enter_tree", &LevelController::_enter_tree);
        godot::register_method("_exit_tree", &LevelController::_exit_tree);
        godot::register_method("_unhandled_input", &LevelController::_unhandled_input);

        godot::register_property<LevelController, real_t>("tileSize", &LevelController::set_tile_size,
                                                          &LevelController::get_tile_size, 128.f);
    }

    void _init() {}

    void _enter_tree() {
        instance = this;
    }

    void _exit_tree() {
        instance = nullptr;
    }

    void _unhandled_input(const godot::Ref<godot::InputEvent> event) {
        if (event->is_action_pressed("ui_up")) move_entities(Vector2<long>(0, -1));
        else if (event->is_action_pressed("ui_down")) move_entities(Vector2<long>(0, 1));
        else if (event->is_action_pressed("ui_left")) move_entities(Vector2<long>(-1, 0));
        else if (event->is_action_pressed("ui_right")) move_entities(Vector2<long>(1, 0));
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

private:
    real_t tileSize = 128.f;

    void move_entities(Vector2<long> movement);
};

#endif //BABA_IS_YOU_LEVEL_CONTROLLER_H
