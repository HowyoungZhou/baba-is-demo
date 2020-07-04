#ifndef BABA_IS_YOU_LEVEL_CONTROLLER_H
#define BABA_IS_YOU_LEVEL_CONTROLLER_H

#include "enums.h"
#include "entity.h"

#include <godot.hpp>
#include <Node2D.hpp>

#include <numeric>
#include <unordered_map>
#include <unordered_set>

class Entity;

struct HashPair {
    template<class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

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

    void register_entity(Entity *entity);

    void unregister_entity(Entity *entity);

private:
    std::unordered_map<Noun, std::unordered_set<Entity *>> nounEntityMap;
    std::unordered_map<std::pair<int, int>, std::unordered_set<Entity *>, HashPair> posEntityMap;

    real_t tileSize;

    std::pair<long, long> getTilePos(const Entity *entity) const;
};

#endif //BABA_IS_YOU_LEVEL_CONTROLLER_H
