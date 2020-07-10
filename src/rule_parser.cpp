#include "rule_parser.h"

antlrcpp::Any RuleParserVisitor::visitExprs(BabaIsYouParser::ExprsContext *context) {
    auto list = std::make_shared<RuleList>();
    for (auto expr : context->expr()) {
        auto res = visit(expr);
        if (!res.is<RuleListPtr>()) continue;
        auto rules = res.as<RuleListPtr>();
        list->insert(list->end(), rules->cbegin(), rules->cend());
    }
    return list;
}

antlrcpp::Any RuleParserVisitor::visitCondition(BabaIsYouParser::ConditionContext *context) {
    std::shared_ptr<Condition> condition;
    if (context->FACING())
        condition = std::make_shared<FacingCondition>();
    else if (context->NEAR())
        condition = std::make_shared<NearCondition>();
    else if (context->ON())
        condition = std::make_shared<OnCondition>();
    else
        throw SyntaxError("Missing condition word in the condition expression.");

    condition->inverted = context->OP_NOT();

    auto list1 = visit(context->expr()[1]).as<TextListPtr>();
    for (auto &item : *list1) {
        condition->objects.push_back(getNoun(item)->noun);
    }

    auto list0 = visit(context->expr()[0]).as<TextListPtr>();
    for (auto &item : *list0) {
        getNoun(item)->conditions.push_back(condition);
    }

    return list0;
}

antlrcpp::Any RuleParserVisitor::visitLonelyCondition(BabaIsYouParser::LonelyConditionContext *context) {
    auto condition = std::make_shared<LonelyCondition>();
    condition->inverted = context->OP_NOT();

    auto list = visit(context->expr()).as<TextListPtr>();
    for (auto &item : *list) {
        getNoun(item)->conditions.push_back(condition);
    }

    return list;
}

antlrcpp::Any RuleParserVisitor::visitVerb(BabaIsYouParser::VerbContext *context) {
    auto resLeft = visit(context->expr()[0]);
    if (!resLeft.is<TextListPtr>()) throw SyntaxError("Different verbs must be joined using AND.");

    auto resRight = visit(context->expr()[1]);
    bool inverted = context->OP_NOT();

    if (resRight.is<TextListPtr>())
        return handleSimpleVerb(getOperator(context), resLeft.as<TextListPtr>(), resRight.as<TextListPtr>(),
                                inverted);
    else if (resRight.is<RuleListPtr>())
        return handleChainedVerb(getOperator(context), resLeft.as<TextListPtr>(), resRight.as<RuleListPtr>(),
                                 inverted);
    else return nullptr;
}

RuleParserVisitor::RuleListPtr
RuleParserVisitor::handleSimpleVerb(Operators op, const RuleParserVisitor::TextListPtr &left,
                                    const RuleParserVisitor::TextListPtr &right, bool inverted) {
    auto rules = std::make_shared<RuleList>();
    switch (op) {
        case Operators::IS:
            for (auto &leftItem : *left) {
                auto leftNoun = getNoun(leftItem);
                for (auto &rightItem : *right) {
                    if (auto prop = std::get_if<Properties>(&rightItem)) {
                        rules->push_back(std::make_shared<PropertyRule>(inverted, *leftNoun, *prop));
                    }
                    else if (auto noun = std::get_if<Noun>(&rightItem)) {
                        rules->push_back(std::make_shared<TransformRule>(inverted, *leftNoun, *noun));
                    }
                }
            }
            break;
        case Operators::HAS:
            handleNounOperators<HasRule>(rules, left, right, inverted);
            break;
        case Operators::MAKE:
            handleNounOperators<MakeRule>(rules, left, right, inverted);
            break;
    }
    return rules;
}

RuleParserVisitor::RuleListPtr
RuleParserVisitor::handleChainedVerb(Operators op, const RuleParserVisitor::TextListPtr &left,
                                     const RuleParserVisitor::RuleListPtr &right, bool inverted) {
    auto hashNoun = [](const Noun &noun) { return std::hash<Nouns>{}(noun.noun); };
    std::unordered_set<Noun, decltype(hashNoun)> rightNouns({}, hashNoun);
    for (auto &rule : *right) rightNouns.insert(rule->noun);
    auto rightList = std::make_shared<TextList>(rightNouns.cbegin(), rightNouns.cend());
    auto rules = handleSimpleVerb(op, left, rightList, inverted);
    right->insert(right->cend(), rules->cbegin(), rules->cend());
    return right;
}

antlrcpp::Any RuleParserVisitor::visitConjunctVerb(BabaIsYouParser::ConjunctVerbContext *context) {
    auto resLeft = visit(context->expr()[0]);
    if (!resLeft.is<RuleListPtr>()) throw SyntaxError("AND should not be used before the first verb.");

    auto resRight = visit(context->expr()[1]);
    if (!resRight.is<TextListPtr>()) throw SyntaxError("Conjunct verbs and chained verbs can not be mixed.");

    bool inverted = context->OP_NOT();
    return handleChainedVerb(getOperator(context), resRight.as<TextListPtr>(), resLeft.as<RuleListPtr>(), inverted);
}
