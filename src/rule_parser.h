#ifndef BABA_IS_YOU_RULE_PARSER_H
#define BABA_IS_YOU_RULE_PARSER_H

#include "rule.h"

#include "BabaIsYouParserBaseVisitor.h"
#include "BabaIsYouLexer.h"

#include <variant>

using TextList = std::vector<std::variant<Noun, Properties>>;
using TextListPtr = std::shared_ptr<TextList>;

using RuleList = std::vector<std::shared_ptr<Rule>>;

class SyntaxError : public std::runtime_error {
public:
    const antlr4::Token *offendingSymbol;

    explicit SyntaxError(const char *message, const antlr4::Token *offendingSymbol = nullptr) :
            std::runtime_error(message), offendingSymbol(offendingSymbol) {}
};

template<class OutIter>
class RuleParserVisitor : public BabaIsYouParserBaseVisitor {
public:
    explicit RuleParserVisitor(OutIter output) : output(output) {}

    antlrcpp::Any visitExprs(BabaIsYouParser::ExprsContext *context) override {
        for (auto expr : context->expr()) visit(expr);
        return nullptr;
    }

private:
    OutIter output;

    static size_t getChildToken(antlr4::tree::ParseTree *tree) {
        return dynamic_cast<antlr4::tree::TerminalNode *>(tree->children.front())->getSymbol()->getType();
    }

    template<class ...Types>
    static Noun *getNoun(std::variant<Types...> &variant) {
        if (auto res = std::get_if<Noun>(&variant)) return res;
        else throw SyntaxError("Property can not appear in this type of expression.");
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

    antlrcpp::Any visitLonelyCondition(BabaIsYouParser::LonelyConditionContext *context) override {
        auto condition = std::make_shared<LonelyCondition>();
        condition->inverted = context->OP_NOT();

        auto list = visit(context->expr()).as<TextListPtr>();
        for (auto &item : *list) {
            getNoun(item)->conditions.push_back(condition);
        }

        return list;
    }

    antlrcpp::Any visitVerb(BabaIsYouParser::VerbContext *context) override {
        auto exprs = context->expr();
        TextListPtr left = visit(exprs[0]), right = visit(exprs[1]);
        bool inverted = context->OP_NOT();

        switch (getOperator(context)) {
            case Operators::IS:
                for (auto &leftItem : *left) {
                    auto leftNoun = getNoun(leftItem);
                    for (auto &rightItem : *right) {
                        if (auto prop = std::get_if<Properties>(&rightItem)) {
                            *output++ = std::make_shared<PropertyRule>(inverted, *leftNoun, *prop);
                        } else if (auto noun = std::get_if<Noun>(&rightItem)) {
                            *output++ = std::make_shared<TransformRule>(inverted, *leftNoun, *noun);
                        }
                    }
                }
                break;
            case Operators::HAS:
                handleNounOperators<HasRule>(left, right, inverted);
                break;
            case Operators::MAKE:
                handleNounOperators<MakeRule>(left, right, inverted);
                break;
            default:;
        }

        return left;
    }

    template<class T>
    void handleNounOperators(const TextListPtr &left, const TextListPtr &right, bool inverted) {
        for (auto &leftItem : *left) {
            auto leftNoun = getNoun(leftItem);
            for (auto &rightItem : *right) {
                *output++ = std::make_shared<T>(inverted, *leftNoun, *getNoun(rightItem));
            }
        }
    }

    template<class T>
    Operators getOperator(T context) {
        if (context->IS()) return Operators::IS;
        if (context->HAS()) return Operators::HAS;
        if (context->MAKE()) return Operators::MAKE;
    }
};

class SyntaxErrorListener : public antlr4::BaseErrorListener {
public:
    void
    syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                const std::string &msg, std::exception_ptr e) override {
        throw SyntaxError(msg.c_str(), offendingSymbol);
    }
};

class RuleParser {
public:
    RuleParser() = delete;

    template<class InIter, class OutIter>
    static void parseRule(InIter begin, InIter end, OutIter output) {
        std::vector<std::unique_ptr<antlr4::Token>> tokens;
        antlr4::CommonTokenFactory factory;
        for (; begin != end; ++begin)
            tokens.push_back(std::make_unique<antlr4::CommonToken>(static_cast<size_t>(*begin)));

        antlr4::ListTokenSource tokenSource(std::move(tokens));
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

        SyntaxErrorListener errorListener;
        parser.removeErrorListeners();
        parser.addErrorListener(&errorListener);

        RuleParserVisitor(output).visit(parser.exprs());
    }
};

#endif //BABA_IS_YOU_RULE_PARSER_H
