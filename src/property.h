#ifndef BABA_IS_YOU_PROPERTY_H
#define BABA_IS_YOU_PROPERTY_H

#include "level_controller.h"
#include "vector2.h"

class Entity;

class Property {
public:
    virtual int get_priority() const { return 0; }

    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const;
};

class MoveProperty : public Property {
public:
    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const override;
};

class StopProperty : public Property {
public:
    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const override {
        return false;
    }
};

extern Property default_property;
extern MoveProperty move_property;
extern StopProperty stop_property;

#endif //BABA_IS_YOU_PROPERTY_H
