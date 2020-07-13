#include "entity.h"
#include "text_entity.h"
#include "directional_entity.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    // TODO: register classes using godot::register_class<T>();
    godot::register_class<LevelController>();
    godot::register_class<Entity>();
    godot::register_class<TextEntity>();
    godot::register_class<DirectionalEntity>();
}
