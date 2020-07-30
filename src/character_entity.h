#ifndef BABA_IS_YOU_CHARACTER_ENTITY_H
#define BABA_IS_YOU_CHARACTER_ENTITY_H

#include "directional_entity.h"

#include <sstream>

class CharacterEntity : public DirectionalEntity {
GODOT_SUBCLASS(CharacterEntity, DirectionalEntity)
public:
    /**
     * Register methods for Godot.
     */
    static void _register_methods() {
        godot::register_property<CharacterEntity, int>("Animation Index", &CharacterEntity::_animation_index, 0);
        godot::register_property<CharacterEntity, int>("Animation Count", &CharacterEntity::_animation_count, 4);
    }

    /**
     * Switch to the next animation.
     */
    void next_animation() {
        _animation_index++;
        _animation_index %= _animation_count;
        update_animation();
    }

protected:
    int _animation_index = 0;
    int _animation_count = 4;

    virtual godot::String get_animation_name() const override {
        return DirectionalEntity::get_animation_name() + (std::stringstream() << _animation_index).str().c_str();
    }
};

#endif //BABA_IS_YOU_CHARACTER_ENTITY_H
