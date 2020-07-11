#include "entity.h"

std::unordered_multimap<Nouns, Entity *> Entity::nounEntityMap;
std::unordered_multimap<TilePosition, Entity *> Entity::posEntityMap;
