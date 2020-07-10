#include "entity.h"

std::unordered_map<Nouns, std::unordered_set<Entity *>> Entity::nounEntityMap;
std::unordered_map<TilePosition, std::unordered_set<Entity *>> Entity::posEntityMap;
