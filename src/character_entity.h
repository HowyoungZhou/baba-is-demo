#ifndef BABA_IS_YOU_CHARACTER_ENTITY_H
#define BABA_IS_YOU_CHARACTER_ENTITY_H

#include "directional_entity.h"

#include <sstream>

class CharacterEntity : public DirectionalEntity {
GODOT_CLASS(CharacterEntity, AnimatedSprite);
public:
    static void _register_methods() {
        godot::register_method("_enter_tree", &CharacterEntity::_enter_tree);
        godot::register_method("_exit_tree", &CharacterEntity::_exit_tree);
        godot::register_property<CharacterEntity, size_t>("Noun", &CharacterEntity::noun, 0,
                                                          GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                                                          GODOT_PROPERTY_HINT_ENUM, kNounsHintString);
        godot::register_property<CharacterEntity, size_t>("Direction", &CharacterEntity::direction_, 3,
                                                          GODOT_METHOD_RPC_MODE_DISABLED,
                                                          GODOT_PROPERTY_USAGE_DEFAULT,
                                                          GODOT_PROPERTY_HINT_ENUM, kDirectionsHintString);
        godot::register_property<CharacterEntity, int>("Animation Index", &CharacterEntity::animation_index_, 1);
        godot::register_property<CharacterEntity, int>("Animation Count", &CharacterEntity::animation_count_, 5);
    }

    void _init() {
        DirectionalEntity::_init();
    }

    void _enter_tree() {
        DirectionalEntity::_enter_tree();
    }

    void _exit_tree() {
        DirectionalEntity::_exit_tree();
    }

    void next_animation() {
        animation_index_++;
        animation_index_ %= animation_count_;
        update_animation();
    }

protected:
    int animation_index_ = 1;
    int animation_count_ = 5;

    virtual godot::String get_animation_name() const override {
        return DirectionalEntity::get_animation_name() + (std::stringstream() << animation_index_).str().c_str();
    }
};

#endif //BABA_IS_YOU_CHARACTER_ENTITY_H
