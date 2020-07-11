#ifndef BABA_IS_YOU_TEXT_H
#define BABA_IS_YOU_TEXT_H

#include "entity.h"
#include "words.h"
#include "rule_parser.h"

class TextEntity : public Entity {
GODOT_CLASS(TextEntity, Node2D)
public:
    static void _register_methods() {
        godot::register_method("_enter_tree", &TextEntity::_enter_tree);
        godot::register_method("_exit_tree", &TextEntity::_exit_tree);
        godot::register_property<TextEntity, size_t>("Text", &TextEntity::word_, 0,
                                                     GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                                                     GODOT_PROPERTY_HINT_ENUM, kWordsHintString);
    }

    void _init() {
        Entity::_init();
        set_noun(Nouns::TEXT);
        properties.push(&move_property);
    }

    void _enter_tree() {
        Entity::_enter_tree();
    }

    void _exit_tree() {
        Entity::_exit_tree();
    }

    void set_word(Words value) {
        word_ = static_cast<size_t>(value) - static_cast<size_t>(Words::ALGAE);
    }

    Words get_word() const {
        return static_cast<Words>(word_ + static_cast<size_t>(Words::ALGAE));
    }

    void set_tile_pos(TilePosition newPos) override {
        Entity::set_tile_pos(newPos);
        rule_check();
    }

    void rule_check() {
        RuleList rules;
        auto tile_dim = LevelController::instance->get_tile_dim();

        for (auto op_pos : operator_pos_) {
            scan_line(op_pos.y, tile_dim.x, true, std::back_inserter(rules));
            scan_line(op_pos.x, tile_dim.y, false, std::back_inserter(rules));
        }

        std::unordered_multimap<Nouns, std::shared_ptr<Rule>> positive, negative;
        for (auto rule : rules) {
            if (rule->inverted) negative.insert(std::make_pair(rule->noun.noun, rule));
            else positive.insert(std::make_pair(rule->noun.noun, rule));
        }

        // remove complementary pairs of rules
        for (auto negative_iter = negative.begin(); negative_iter != negative.end();) {
            bool rule_deleted = false;
            for (auto pos = positive.equal_range(negative_iter->first); pos.first != pos.second;) {
                // pos.first is the current iterator of positive list
                if (negative_iter->second->complementary(*pos.first->second)) {
                    pos.first = positive.erase(pos.first);        // remove the rule from the positive list
                    negative_iter = negative.erase(negative_iter);// remove the rule from the negative list
                    rule_deleted = true;
                    break;// handle the next negative rule
                }
                ++pos.first;// else, search the next positive rule
            }
            if (!rule_deleted) ++negative_iter;// if the iterator was not increased before, do it here
        }

        for (auto pair : positive) pair.second->apply();
        for (auto pair : negative) pair.second->revert();
    }

protected:
    size_t word_ = 0;
    std::unordered_set<TilePosition> operator_pos_;

    void update_tile_pos() override {
        Entity::update_tile_pos();
        auto word = static_cast<size_t>(get_word());
        if (word < static_cast<size_t>(Operators::ABOVE) || word > static_cast<size_t>(Operators::WITHOUT)) return;
        operator_pos_.insert(get_tile_pos());
    }

    template<class OutIter>
    void scan_line(long index, long length, bool x_axis, OutIter output) {
        std::vector<Words> words;
        for (long cursor = 0; cursor < length; ++cursor) {
            std::vector<const Entity *> entities;
            get_entities_at_pos(x_axis ? TilePosition(cursor, index) : TilePosition(index, cursor),
                                std::back_inserter(entities));
            for (auto entity : entities) {
                if (typeid(*entity) != typeid(const TextEntity)) continue;
                words.push_back(dynamic_cast<const TextEntity *>(entity)->get_word());
                break;
            }
        }
        try {
            RuleParser::parseRule(words.cbegin(), words.cend(), output);
        }
        catch (SyntaxError &e) {
            std::cout << "Syntax error at " << std::string(x_axis ? "row " : "column ")
                      << index << ": " << e.what() << std::endl;
        }
    }
};

#endif //BABA_IS_YOU_TEXT_H
