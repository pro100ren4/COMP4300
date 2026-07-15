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
	m_entitiesToAdd.push_back(entity);

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

bool EntityManager::isEntityNotAlive(std::shared_ptr<Entity> entity)
{
	return !(entity->m_alive);
}
 
void EntityManager::update()
{
  for ( auto &entityToAdd: m_entitiesToAdd)
  {
    m_entities.push_back(entityToAdd);
    m_entitiesMap[entityToAdd->m_tag].push_back(entityToAdd);
  }
  m_entitiesToAdd.clear();

  m_entities.erase(
    std::remove_if(m_entities.begin(), m_entities.end(), [] (std::shared_ptr<Entity> e) { return !(e->m_alive); }),
    m_entities.end()
  );

  for (auto it = m_entitiesMap.begin(); it != m_entitiesMap.end(); ++it)
  {
    auto& vec = it->second;

    vec.erase(
        std::remove_if(vec.begin(), vec.end(), [] (std::shared_ptr<Entity> e) { return !(e->m_alive); }),
        vec.end()
    );
  }
}
