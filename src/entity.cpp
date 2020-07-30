#include "entity.h"

std::unordered_multimap<Nouns, Entity *> Entity::_noun_entity_map;
std::unordered_multimap<TilePosition, Entity *> Entity::_pos_entity_map;
