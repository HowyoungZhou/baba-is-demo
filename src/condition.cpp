#include "condition.h"
#include "entity.h"

bool OnCondition::eval(const Entity *entity) {
    auto range = Entity::get_entities_at_pos(entity->get_tile_pos());
    std::unordered_set<Nouns> nouns;
    for (auto iter = range.first; iter != range.second; ++iter)
        if (iter->second != entity) nouns.insert(iter->second->get_noun());
    for (auto noun : objects)
        if (nouns.find(noun) == nouns.cend()) return false;
    return true;
}
