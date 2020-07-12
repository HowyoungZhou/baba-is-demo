#ifndef BABA_IS_YOU_CONDITION_H
#define BABA_IS_YOU_CONDITION_H

#include "words.h"

#include <vector>

class Entity;

class Condition {
public:
    virtual ~Condition() = default;

    bool inverted = false;
    std::vector<Nouns> objects;

    virtual bool operator==(const Condition &other) {
        return inverted == other.inverted && objects == other.objects;
    }

    virtual bool eval(const Entity *entity) = 0;
};

class OnCondition : public Condition {
public:
    bool eval(const Entity *entity) override;
};

class NearCondition : public Condition {
public:
    bool eval(const Entity *entity) override { return true; }
};

class FacingCondition : public Condition {
public:
    bool eval(const Entity *entity) override { return true; }
};

class LonelyCondition : public Condition {
public:
    bool eval(const Entity *entity) override { return true; }
};

#endif //BABA_IS_YOU_CONDITION_H
