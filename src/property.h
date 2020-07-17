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

    virtual bool on_collision(Entity *source, Entity *target, TilePosition movement) const;

    virtual void on_registered(Entity *entity) const {}

    virtual void on_destroyed(Entity *entity) const {}
};

class PushProperty : public Property {
public:
    Properties get_type() override { return Properties::PUSH; }

    virtual bool on_collision(Entity *source, Entity *target, TilePosition movement) const override;
};

class StopProperty : public Property {
public:
    Properties get_type() override { return Properties::STOP; }

    virtual bool on_collision(Entity *source, Entity *target, TilePosition movement) const override {
        return false;
    }
};

class YouProperty : public Property {
public:
    Properties get_type() override { return Properties::YOU; }

    void on_registered(Entity *entity) const override {
        LevelController::instance->controlled_entities.insert(entity);
    }
};

class DefeatProperty : public Property {
public:
    virtual Properties get_type() { return Properties::DEFEAT; }
    bool on_collision(Entity *source, Entity *target, TilePosition movement) const override;
};

// added by zdz 20.07.16
class SinkProperty : public Property {
public:
    Properties get_type() override { return Properties::SINK; }

    virtual bool on_collision(Entity *source, Entity *target, TilePosition movement) const override;
};

class MeltProperty : public Property {
public:
    Properties get_type() override { return Properties::MELT; }
};

class HotProperty : public Property {
public:
    Properties get_type() override { return Properties::HOT; }

    virtual bool on_collision(Entity *source, Entity *target, TilePosition movement) const override;
};

class WinProperty : public Property {
public:
    Properties get_type() override { return Properties::WIN; }

    virtual bool on_collision(Entity *source, Entity *target, TilePosition movement) const override;
};

class OpenProperty : public Property {
public:
    Properties get_type() override { return Properties::OPEN; }
};

class ShutProperty : public Property {
public:
    Properties get_type() override { return Properties::SHUT; }

    virtual bool on_collision(Entity *source, Entity *target, TilePosition movement) const override;
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

    bool on_collision(Entity *source, Entity *target, TilePosition movement) const {
        for (auto prop : properties)
            if (prop->enabled(target))
                return prop->on_collision(source, target, movement);
        return true;
    }

    void on_destroyed(Entity *entity) const {
        for (auto prop : properties)
            if (prop->enabled(entity))
                prop->on_destroyed(entity);
    }

    auto get_properties_of_type(Properties type) const {
        return props_map.equal_range(type);
    }

    bool has_property(Properties type) const {
        auto range = get_properties_of_type(type);
        return range.first != range.second;
    }

private:
    std::set<Property *, PropertyPriorityComparer> properties;
    std::unordered_multimap<Properties, Property *> props_map;

    void delete_properties() {
        for (auto prop : properties) delete prop;
    }
};

#endif //BABA_IS_YOU_PROPERTY_H
