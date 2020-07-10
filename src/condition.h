#ifndef BABA_IS_YOU_CONDITION_H
#define BABA_IS_YOU_CONDITION_H

#include "words.h"

#include <vector>

class Condition {
public:
    virtual ~Condition() = default;

    bool inverted = false;
    std::vector<Nouns> objects;

    virtual bool eval() = 0;
};

class OnCondition : public Condition {
public:
    bool eval() override { return false; }
};

class NearCondition : public Condition {
public:
    bool eval() override { return false; }
};

class FacingCondition : public Condition {
public:
    bool eval() override { return false; }
};

class LonelyCondition : public Condition {
public:
    bool eval() override { return false; }
};

#endif //BABA_IS_YOU_CONDITION_H
