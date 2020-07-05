#ifndef BABA_IS_YOU_LEVEL_CONTROLLER_H
#define BABA_IS_YOU_LEVEL_CONTROLLER_H

#include "enums.h"

#include <godot.hpp>
#include <Node2D.hpp>

#include <numeric>
#include <unordered_map>
#include <unordered_set>

class Entity;

class LevelController : public godot::Node2D {
GODOT_CLASS(LevelController, godot::Node2D);
public:
    static LevelController *instance;

    static void _register_methods() {
        godot::register_method("_enter_tree", &LevelController::_enter_tree);
        godot::register_method("_exit_tree", &LevelController::_exit_tree);

        godot::register_property<LevelController, real_t>("tileSize", &LevelController::tileSize, 128.f);
    }

    void _init() {}

    void _enter_tree() {
        instance = this;
    }

    void _exit_tree() {
        instance = nullptr;
    }

    real_t get_tile_size() const { return tileSize; }

private:
    real_t tileSize;
};

#endif //BABA_IS_YOU_LEVEL_CONTROLLER_H
