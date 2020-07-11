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

    static void rule_check();

protected:
    size_t word_ = 0;

    template<class OutIter>
    static void scan_line(long index, long length, bool x_axis, OutIter output) {
        std::vector<Words> words;
        for (long cursor = 0; cursor < length; ++cursor) {
            std::vector<const Entity *> entities;
            get_entities_at_pos(x_axis ? TilePosition(cursor, index) : TilePosition(index, cursor),
                                std::back_inserter(entities));
            auto found_text = false;
            for (auto entity : entities) {
                if (typeid(*entity) != typeid(const TextEntity)) continue;
                words.push_back(dynamic_cast<const TextEntity *>(entity)->get_word());
                found_text = true;
                break;
            }
            if (found_text || words.empty()) continue;
            try {
                RuleParser::parseRule(words.cbegin(), words.cend(), output);
            } catch (SyntaxError &e) {
                std::cout << "Syntax error at " << std::string(x_axis ? "row " : "column ")
                        << index << ": " << e.what() << std::endl;
            }
            words.clear();
        }        
    }
};

#endif //BABA_IS_YOU_TEXT_H
