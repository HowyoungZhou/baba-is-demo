#ifndef BABA_IS_YOU_RULE_H
#define BABA_IS_YOU_RULE_H

#include "words.h"
#include "condition.h"

#include <vector>
#include <memory>

struct Noun {
    bool inverted = false;
    Nouns noun;
    std::vector<std::shared_ptr<Condition>> conditions;

    explicit Noun(Nouns noun) : noun(noun) {}

    bool operator==(const Noun &other) const {
        return inverted == other.inverted && noun == other.noun && conditions == other.conditions;
    }
};

class Rule {
public:
    bool inverted = false;
    Noun noun;

    explicit Rule(bool inverted, Noun noun) : inverted(inverted), noun(std::move(noun)) {}

    virtual ~Rule() = default;

    virtual void apply() = 0;
};

class PropertyRule : public Rule {
public:
    Properties property;

    PropertyRule(bool inverted, Noun noun, Properties property) : Rule(inverted, std::move(noun)), property(property) {}

    void apply() override {}
};


class NounRule : public Rule {
public:
    Noun object;

    NounRule(bool inverted, Noun noun, Noun object) : Rule(inverted, std::move(noun)), object(std::move(object)) {}
};

class TransformRule : public NounRule {
public:
    TransformRule(bool inverted, Noun noun, Noun object) : NounRule(inverted, noun, object) {}

    void apply() override {}
};

class HasRule : public NounRule {
public:
    HasRule(bool inverted, Noun noun, Noun object) : NounRule(inverted, std::move(noun), std::move(object)) {}

    void apply() override {}
};

class MakeRule : public NounRule {
public:
    MakeRule(bool inverted, Noun noun, Noun object) : NounRule(inverted, std::move(noun), std::move(object)) {}

    void apply() override {}
};

#endif //BABA_IS_YOU_RULE_H
