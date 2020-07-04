#include "entity.h"

void Entity::_enter_tree() {
    LevelController::instance->register_entity(this);
}

void Entity::_exit_tree() {
    LevelController::instance->unregister_entity(this);
}
