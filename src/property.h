#ifndef BABA_IS_YOU_PROPERTY_H
#define BABA_IS_YOU_PROPERTY_H

#include "level_controller.h"
#include "vector2.h"
#include "condition.h"

class Entity;

class Property {
public:
    std::vector<std::shared_ptr<Condition>> conditions;

    virtual ~Property() = default;

    virtual int get_priority() const { return 0; }

    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const;

    virtual void on_registered(Entity *source) { }
};

class PushProperty : public Property {
public:
    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const override;
};

class StopProperty : public Property {
public:
    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const override {
        return false;
    }
};

class YouProperty : public Property {
public:
    void on_registered(Entity *source) override {
        LevelController::instance->controlled_entities.insert(source);
    }
};

#endif //BABA_IS_YOU_PROPERTY_H
