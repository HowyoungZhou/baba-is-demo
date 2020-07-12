#ifndef BABA_IS_YOU_PROPERTY_H
#define BABA_IS_YOU_PROPERTY_H

#include "level_controller.h"
#include "vector2.h"
#include "condition.h"

#include <set>

class Entity;

class Property {
public:
    std::vector<std::shared_ptr<Condition>> conditions;

    virtual ~Property() = default;

    bool enabled(Entity *entity) {
        for (const auto &condition : conditions)
            if (!condition->eval(entity)) return false;
        return true;
    }

    virtual Properties get_type() = 0;

    virtual int get_priority() const { return 0; }

    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const;

    virtual void on_registered(Entity *entity) {}
};

class PushProperty : public Property {
public:
    Properties get_type() override { return Properties::PUSH; }

    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const override;
};

class StopProperty : public Property {
public:
    Properties get_type() override { return Properties::STOP; }

    virtual bool on_collision(const Entity *source, Entity *target, TilePosition movement) const override {
        return false;
    }
};

class YouProperty : public Property {
public:
    Properties get_type() override { return Properties::YOU; }

    void on_registered(Entity *entity) override {
        LevelController::instance->controlled_entities.insert(entity);
    }
};

struct PropertyPriorityComparer {
    bool operator()(const Property *prop1, const Property *prop2) const {
        return prop1->get_priority() < prop2->get_priority();
    }
};

class PropertyList {
public:
    ~PropertyList() {
        delete_properties();
    }

    void insert(Property *property) {
        properties.insert(property);
        props_map.insert({property->get_type(), property});
    }

    void clear() {
        delete_properties();
        properties.clear();
        props_map.clear();
    }

    bool on_collision(const Entity *source, Entity *target, TilePosition movement) {
        for (auto prop : properties)
            if (prop->enabled(target))
                return prop->on_collision(source, target, movement);
        return true;
    }

    auto get_properties_of_type(Properties type) {
        return props_map.equal_range(type);
    }

private:
    std::set<Property *, PropertyPriorityComparer> properties;
    std::unordered_multimap<Properties, Property *> props_map;

    void delete_properties() {
        for (auto prop : properties) delete prop;
    }
};

#endif //BABA_IS_YOU_PROPERTY_H
