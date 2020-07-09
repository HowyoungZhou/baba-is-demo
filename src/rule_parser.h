#ifndef BABA_IS_YOU_RULE_PARSER_H
#define BABA_IS_YOU_RULE_PARSER_H

#include "rule.h"

#include "BabaIsYouParserBaseVisitor.h"
#include "BabaIsYouLexer.h"

#include <variant>

class RuleSyntaxError : std::exception {
public:
    explicit RuleSyntaxError(const char *message) : std::exception(message) {}
};

class RuleParserVisitor : public BabaIsYouParserBaseVisitor {
public:
    using TextList = std::vector<std::variant<Noun, Properties>>;
    using RuleList = std::vector<Rule *>;
    using TextListPtr = std::shared_ptr<TextList>;
    using RuleListPtr = std::shared_ptr<RuleList>;

    antlrcpp::Any visitExprs(BabaIsYouParser::ExprsContext *context) override {
        RuleList list;
        for (auto expr : context->expr()) {
            auto res = visit(expr);
            if (!res.is<RuleListPtr>()) continue;
            auto &rules = res.as<RuleListPtr>();
            list.insert(list.end(), rules->cbegin(), rules->cend());
        }
        return std::make_shared<RuleList>(list);
    }

private:
    static size_t getChildToken(antlr4::tree::ParseTree *tree) {
        return dynamic_cast<antlr4::tree::TerminalNode *>(tree->children.front())->getSymbol()->getType();
    }

    template<class ...Types>
    static Noun *getNoun(std::variant<Types...> &variant) {
        if (auto res = std::get_if<Noun>(&variant)) return res;
        else throw RuleSyntaxError("Property can not appear in this type of expression.");
    }

    antlrcpp::Any visitNoun(BabaIsYouParser::NounContext *context) override {
        TextList vector({Noun(static_cast<Nouns>(getChildToken(context)))});
        return std::make_shared<TextList>(vector);
    }

    antlrcpp::Any visitProperty(BabaIsYouParser::PropertyContext *context) override {
        return std::make_shared<TextList>(TextList({static_cast<Properties>(getChildToken(context))}));
    }

    antlrcpp::Any visitNotExpr(BabaIsYouParser::NotExprContext *context) override {
        auto list = visit(context->expr()).as<TextListPtr>();
        for (auto &item : *list) {
            if (auto noun = std::get_if<Noun>(&item)) noun->inverted = !noun->inverted;
        }
        return list;
    }

    antlrcpp::Any visitAndExpr(BabaIsYouParser::AndExprContext *context) override {
        auto exprs = context->expr();
        TextListPtr list0 = visit(exprs[0]), list1 = visit(exprs[1]);
        list0->insert(list0->cend(), list1->cbegin(), list1->cend());
        return list0;
    }

    antlrcpp::Any visitCondition(BabaIsYouParser::ConditionContext *context) override {
        Condition *condition;
        if (context->FACING())
            condition = new FacingCondition();
        else if (context->NEAR())
            condition = new NearCondition();
        else if (context->ON())
            condition = new OnCondition();
        else
            throw RuleSyntaxError("Missing condition word in the condition expression.");

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

    antlrcpp::Any visitLonelyCondition(BabaIsYouParser::LonelyConditionContext *context) override {
        auto condition = new LonelyCondition;
        condition->inverted = context->OP_NOT();

        auto list = visit(context->expr()).as<TextListPtr>();
        for (auto &item : *list) {
            getNoun(item)->conditions.push_back(condition);
        }

        return list;
    }

    antlrcpp::Any visitVerb(BabaIsYouParser::VerbContext *context) override {
        auto resLeft = visit(context->expr()[0]);
        if (!resLeft.is<TextListPtr>()) throw RuleSyntaxError("Different verbs must be joined using AND.");

        auto resRight = visit(context->expr()[1]);
        bool inverted = context->OP_NOT();

        if (resRight.is<TextListPtr>())
            return handleSimpleVerb(context, resLeft.as<TextListPtr>(), resRight.as<TextListPtr>(), inverted);
        else if (resRight.is<RuleListPtr>())
            return handleChainedVerb(context, resLeft.as<TextListPtr>(), resRight.as<RuleListPtr>(), inverted);
        else return nullptr;
    }

    antlrcpp::Any visitConjunctVerb(BabaIsYouParser::ConjunctVerbContext *context) override {
        return nullptr;
    }

    static RuleListPtr
    handleSimpleVerb(BabaIsYouParser::VerbContext *context, const TextListPtr &left, const TextListPtr &right,
                     bool inverted) {
        RuleList rules;
        try {
            if (context->IS()) {
                for (auto &leftItem : *left) {
                    auto leftNoun = getNoun(leftItem);
                    for (auto &rightItem : *right) {
                        if (auto prop = std::get_if<Properties>(&rightItem)) {
                            rules.push_back(new PropertyRule(inverted, *leftNoun, *prop));
                        }
                        else if (auto noun = std::get_if<Noun>(&rightItem)) {
                            rules.push_back(new TransformRule(inverted, *leftNoun, *noun));
                        }
                    }
                }
            }
            else if (context->HAS()) {
                for (auto &leftItem : *left) {
                    auto leftNoun = getNoun(leftItem);
                    for (auto &rightItem : *right) {
                        rules.push_back(new HasRule(inverted, *leftNoun, *getNoun(rightItem)));
                    }
                }
            }
            else if (context->MAKE()) {
                for (auto &leftItem : *left) {
                    auto leftNoun = getNoun(leftItem);
                    for (auto &rightItem : *right) {
                        rules.push_back(new MakeRule(inverted, *leftNoun, *getNoun(rightItem)));
                    }
                }
            }
        }
        catch (RuleSyntaxError &) {
            for (auto rule : rules) delete rule;
            throw;
        }
        return std::make_shared<RuleList>(rules);
    }

    static RuleListPtr
    handleChainedVerb(BabaIsYouParser::VerbContext *context, const TextListPtr &left, const RuleListPtr &right,
                      bool inverted) {
        return RuleListPtr();
    }
};

class RuleParser {
public:
    RuleParser() = delete;

    template<class InIter, class OutIter>
    static void parseRule(InIter begin, InIter end, OutIter output) {
        std::vector<std::unique_ptr<antlr4::Token>> tokens;
        for (; begin != end; ++begin) tokens.emplace_back(antlr4::CommonToken(*begin));

        antlr4::ListTokenSource tokenSource(tokens);
        parseRule(&tokenSource, output);
    }

    template<class OutIter>
    static void parseRule(const std::string &text, OutIter output) {
        antlr4::ANTLRInputStream inStream(text);
        BabaIsYouLexer lexer(&inStream);
        parseRule(&lexer, output);
    }

private:
    template<class OutIter>
    static void parseRule(antlr4::TokenSource *source, OutIter output) {
        antlr4::CommonTokenStream tokenStream(source);
        BabaIsYouParser parser(&tokenStream);
        RuleParserVisitor visitor;
        RuleParserVisitor::RuleListPtr list = visitor.visitExprs(parser.exprs());
        std::copy(list->cbegin(), list->cend(), output);
    }
};

#endif //BABA_IS_YOU_RULE_PARSER_H
