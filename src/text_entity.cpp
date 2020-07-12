#include "text_entity.h"

void TextEntity::rule_check() {
    RuleList rules(Rule::base_rules);
    auto tile_dim = LevelController::instance->get_tile_dim();

    // find rows and columns having TEXTs in it
    std::unordered_set<long> rows, columns;
    auto range = find_entities_of_noun(Nouns::TEXT);
    for (auto iter = range.first; iter != range.second; ++iter) {
        auto word = dynamic_cast<TextEntity *>(iter->second)->get_word();
        if (word < Words::ABOVE || word > Words::WITHOUT) continue;
        auto pos = iter->second->get_tile_pos();
        columns.insert(pos.x);
        rows.insert(pos.y);
    }

    for (auto row : rows)
        scan_line(row, tile_dim.x, true, std::back_inserter(rules));

    for (auto column : columns)
        scan_line(column, tile_dim.y, false, std::back_inserter(rules));

    // classify rules into positive and negative
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

    for (auto pair : posEntityMap) pair.second->properties.clear();
    LevelController::instance->controlled_entities.clear();
    // TODO: undo transformation

    for (auto pair : positive) pair.second->apply_all();
    for (auto pair : negative) pair.second->revert_all();
}
