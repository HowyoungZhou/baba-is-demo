#ifndef BABA_IS_YOU_ENTITY_H
#define BABA_IS_YOU_ENTITY_H

#include "enums.h"
#include "property.h"
#include "level_controller.h"

#include <Godot.hpp>
#include <Sprite.hpp>

#include <queue>

class Entity : public godot::Sprite {
GODOT_CLASS(Entity, Sprite);
public:
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

    void _enter_tree();

    void _exit_tree();

private:
    std::priority_queue<Property> properties;
    size_t noun;
};

#endif //BABA_IS_YOU_ENTITY_H
