#include "rule.h"

const std::vector<std::shared_ptr<Rule>> Rule::base_rules{{
        std::make_shared<PropertyRule>(false, Noun(Nouns::TEXT), Properties::PUSH),
        std::make_shared<PropertyRule>(false, Noun(Nouns::LEVEL), Properties::STOP),
        std::make_shared<PropertyRule>(false, Noun(Nouns::CURSOR), Properties::SELECT),
}};
