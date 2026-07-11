#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>

#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntitiesVector;
typedef std::map<std::string, EntitiesVector> EntitiesMap;

class EntityManager {
	size_t m_totalEntities = 0;

	EntitiesVector m_entities;
	EntitiesMap m_entitiesMap;
	
public:
	EntityManager() {}
	~EntityManager();

	std::shared_ptr<Entity> addEntity(const std::string& tag);

	EntitiesVector& getEntities();
	EntitiesVector& getEntities(const std::string &tag);

	void update();
	bool isEntitytNotAlive(std::shared_ptr<Entity> entity);
};
