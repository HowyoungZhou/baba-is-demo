#ifndef BABA_IS_YOU_DIRECTIONAL_ENTITY_H
#define BABA_IS_YOU_DIRECTIONAL_ENTITY_H

#include "entity.h"

class DirectionalEntity : public Entity {
GODOT_SUBCLASS(DirectionalEntity, Entity)
public:
    static void _register_methods() {
        godot::register_method("_enter_tree", &DirectionalEntity::_enter_tree);

        godot::register_property<DirectionalEntity, size_t>("Direction", &DirectionalEntity::direction_, 3,
                                                            GODOT_METHOD_RPC_MODE_DISABLED,
                                                            GODOT_PROPERTY_USAGE_DEFAULT,
                                                            GODOT_PROPERTY_HINT_ENUM, kDirectionsHintString);
    }

    void _enter_tree() {
        update_animation();
    }

    void set_direction(Directions value) {
        direction_ = static_cast<size_t>(value) - static_cast<size_t>(Directions::UP);
        update_animation();
    }

    Directions get_direction() const {
        return static_cast<Directions>(direction_ + static_cast<size_t>(Directions::UP));
    }

protected:
    size_t direction_ = 3;

    virtual godot::String get_animation_name() const {
        switch (get_direction()) {
            case Directions::UP:
                return "up";
            case Directions::DOWN:
                return "down";
            case Directions::LEFT:
                return "left";
            case Directions::RIGHT:
                return "right";
        }
    }

    virtual void update_animation() {
        set_animation(get_animation_name());
    }
};

#endif //BABA_IS_YOU_DIRECTIONAL_ENTITY_H
