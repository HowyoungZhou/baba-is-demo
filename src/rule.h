#ifndef BABA_IS_YOU_RULE_H
#define BABA_IS_YOU_RULE_H

#include "words.h"
#include "condition.h"
#include "entity.h"

#include <vector>
#include <memory>

struct Noun {
    bool inverted = false;
    Nouns noun;
    std::vector<std::shared_ptr<Condition>> conditions;

    explicit Noun(Nouns noun) : noun(noun) {}

    bool operator==(const Noun &other) const {
        if (inverted != other.inverted || noun != other.noun) return false;
        if (conditions.empty() && other.conditions.empty()) return true;
        if (conditions.size() != other.conditions.size()) return false;
        auto equal = [](std::shared_ptr<Condition> ptr1, std::shared_ptr<Condition> ptr2) { return *ptr1 == *ptr2; };
        using Iter = std::vector<std::shared_ptr<Condition>>::const_iterator;
        return std::equal<Iter, Iter, decltype(equal)>(conditions.cbegin(), conditions.cend(), other.conditions.cbegin(), equal);
    }
};

class Rule {
public:
    static const std::vector<std::shared_ptr<Rule>> base_rules;

    bool inverted = false;
    Noun noun;

    explicit Rule(bool inverted, Noun noun) : inverted(inverted), noun(std::move(noun)) {}

    virtual ~Rule() = default;

    virtual bool complementary(const Rule &other) const {
        return typeid(*this) == typeid(other) && noun == other.noun && inverted != other.inverted;
    }

    virtual void apply_all() {
        switch (noun.noun) {
            default:
                auto range = Entity::find_entities_of_noun(noun.noun);
                for (auto iter = range.first; iter != range.second; ++iter) apply(iter->second);
                break;
        }
    }

    virtual void revert_all() { }

    virtual void apply(Entity *entity) { }
};

class PropertyRule : public Rule {
public:
    Properties property;

    PropertyRule(bool inverted, Noun noun, Properties property) : Rule(inverted, std::move(noun)), property(property) {}

    bool complementary(const Rule &other) const override {
        return Rule::complementary(other) && property == dynamic_cast<const PropertyRule &>(other).property;
    }

    void apply(Entity *entity) override {
        switch (property) {
            case Properties::PUSH:
                add_property<PushProperty>(entity);
                break;
            case Properties::STOP:
                add_property<StopProperty>(entity);
                break;
            case Properties::YOU:
                add_property<YouProperty>(entity);
                break;
        }
    }

private:
    template<class T>
    void add_property(Entity *entity) {
        auto prop = std::make_unique<T>();
        prop->conditions.insert(prop->conditions.end(), noun.conditions.cbegin(), noun.conditions.cend());
        prop->on_registered(entity);
        entity->properties.push(std::move(prop));
    }
};


class NounRule : public Rule {
public:
    Noun object;

    NounRule(bool inverted, Noun noun, Noun object) : Rule(inverted, std::move(noun)), object(std::move(object)) {}

    bool complementary(const Rule &other) const override {
        return Rule::complementary(other) && object == dynamic_cast<const NounRule &>(other).object;
    }
};

class TransformRule : public NounRule {
public:
    TransformRule(bool inverted, Noun noun, Noun object) : NounRule(inverted, noun, object) {}

    void apply(Entity *entity) override {}
};

class HasRule : public NounRule {
public:
    HasRule(bool inverted, Noun noun, Noun object) : NounRule(inverted, std::move(noun), std::move(object)) {}

    void apply(Entity *entity) override {}
};

class MakeRule : public NounRule {
public:
    MakeRule(bool inverted, Noun noun, Noun object) : NounRule(inverted, std::move(noun), std::move(object)) {}

    void apply(Entity *entity) override {}
};

#endif //BABA_IS_YOU_RULE_H
