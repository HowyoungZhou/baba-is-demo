#ifndef BABA_IS_YOU_TEXT_H
#define BABA_IS_YOU_TEXT_H

#include "entity.h"
#include "words.h"
#include "rule_parser.h"

class TextEntity : public Entity {
GODOT_SUBCLASS(TextEntity, Entity)
public:
    static void _register_methods() {
        godot::register_property<TextEntity, size_t>("Text", &TextEntity::word_, 0,
                                                     GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                                                     GODOT_PROPERTY_HINT_ENUM, kWordsHintString);
        godot::register_property<TextEntity, size_t>("Noun", &TextEntity::noun, 76,
                                                 GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT,
                                                 GODOT_PROPERTY_HINT_ENUM, kNounsHintString);
    }

    void _init() {
        Entity::_init();
        set_noun(Nouns::TEXT);
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
            auto range = get_entities_at_pos(x_axis ? TilePosition(cursor, index) : TilePosition(index, cursor));
            auto found_text = false;
            for (auto iter = range.first; iter != range.second; ++iter) {
                if (const auto text_entity = dynamic_cast<const TextEntity *>(iter->second)) {
                    words.push_back(text_entity->get_word());
                    found_text = true;
                    break;
                }
            }
            if (words.empty()) continue;
            if (found_text && cursor < length - 1) continue;
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
