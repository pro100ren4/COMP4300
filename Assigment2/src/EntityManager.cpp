#include <vector>
#include <memory>
#include <map>
#include <string>

#include "Entity.h"
#include "EntityManager.h"

EntityManager::~EntityManager()
{
	m_entities.clear();
	m_entitiesMap.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	m_entities.push_back(entity);
	m_entitiesMap[tag].push_back(entity);

	return entity;
}

EntitiesVector& EntityManager::getEntities()
{
	return m_entities;
}

EntitiesVector& EntityManager::getEntities(const std::string& tag)
{
	return m_entitiesMap[tag];
}

bool EntityManager::isEntitytNotAlive(std::shared_ptr<Entity> entity)
{
	return !(entity->m_alive);
}
 
void EntityManager::update()
{
	std::remove_if(m_entities.begin(), 
				   m_entities.end(), 
				   [] (std::shared_ptr<Entity> e) { return !(e->m_alive); });
}