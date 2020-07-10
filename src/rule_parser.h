#ifndef BABA_IS_YOU_RULE_PARSER_H
#define BABA_IS_YOU_RULE_PARSER_H

#include "rule.h"

#include "BabaIsYouParserBaseVisitor.h"
#include "BabaIsYouLexer.h"

#include <variant>

using TextList = std::vector<std::variant<Noun, Properties>>;
using RuleList = std::vector<std::shared_ptr<Rule>>;
using TextListPtr = std::shared_ptr<TextList>;
using RuleListPtr = std::shared_ptr<RuleList>;

class SyntaxError : std::runtime_error {
public:
    const antlr4::Token *offendingSymbol;

    explicit SyntaxError(const char *message, const antlr4::Token *offendingSymbol = nullptr) : std::runtime_error(message), offendingSymbol(offendingSymbol) {}
};

class RuleParserVisitor : public BabaIsYouParserBaseVisitor {
public:
    antlrcpp::Any visitExprs(BabaIsYouParser::ExprsContext *context) override;

private:
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

    antlrcpp::Any visitCondition(BabaIsYouParser::ConditionContext *context) override;

    antlrcpp::Any visitLonelyCondition(BabaIsYouParser::LonelyConditionContext *context) override;

    antlrcpp::Any visitVerb(BabaIsYouParser::VerbContext *context) override;

    antlrcpp::Any visitConjunctVerb(BabaIsYouParser::ConjunctVerbContext *context) override;

    static RuleListPtr
    handleSimpleVerb(Operators op, const TextListPtr &left, const TextListPtr &right, bool inverted);

    static RuleListPtr
    handleChainedVerb(Operators op, const TextListPtr &left, const RuleListPtr &right,
                      bool inverted);

    template<class T>
    static void handleNounOperators(const RuleListPtr &rules, const TextListPtr &left, const TextListPtr &right, bool inverted) {
        for (auto &leftItem : *left) {
            auto leftNoun = getNoun(leftItem);
            for (auto &rightItem : *right) {
                rules->push_back(std::make_shared<T>(inverted, *leftNoun, *getNoun(rightItem)));
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
        for (; begin != end; ++begin) tokens.push_back(std::make_unique<antlr4::CommonToken>(static_cast<size_t>(*begin)));

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

        RuleParserVisitor visitor;
        RuleListPtr list = visitor.visitExprs(parser.exprs());
        std::copy(list->cbegin(), list->cend(), output);
    }
};

#endif //BABA_IS_YOU_RULE_PARSER_H
