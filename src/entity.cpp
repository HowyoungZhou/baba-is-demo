#include "entity.h"

std::unordered_map<Noun, std::unordered_set<Entity *>> Entity::nounEntityMap;
std::unordered_map<TilePosition, std::unordered_set<Entity *>, HashVector2> Entity::posEntityMap;
