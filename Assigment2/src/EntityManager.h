#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>

#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntitiesVector;

class EntityManager {
	size_t m_totalEntities = 0;

	EntitiesVector m_entities;
	std::map<std::string, EntitiesVector> m_entitiesMap;
	
public:
	EntityManager() {}
	~EntityManager();

	std::shared_ptr<Entity> addEntity(const std::string& tag);

	EntitiesVector& getEntities();
	EntitiesVector& getEntities(const std::string &tag);

	void update();
};
