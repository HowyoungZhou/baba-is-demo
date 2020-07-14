#ifndef BABA_IS_YOU_CHARACTER_ENTITY_H
#define BABA_IS_YOU_CHARACTER_ENTITY_H

#include "directional_entity.h"

#include <sstream>

class CharacterEntity : public DirectionalEntity {
GODOT_SUBCLASS(CharacterEntity, DirectionalEntity)
public:
    static void _register_methods() {
        godot::register_property<CharacterEntity, int>("Animation Index", &CharacterEntity::animation_index_, 0);
        godot::register_property<CharacterEntity, int>("Animation Count", &CharacterEntity::animation_count_, 4);
    }

    void next_animation() {
        animation_index_++;
        animation_index_ %= animation_count_;
        update_animation();
    }

protected:
    int animation_index_ = 0;
    int animation_count_ = 4;

    virtual godot::String get_animation_name() const override {
        return DirectionalEntity::get_animation_name() + (std::stringstream() << animation_index_).str().c_str();
    }
};

#endif //BABA_IS_YOU_CHARACTER_ENTITY_H
