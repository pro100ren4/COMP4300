#include "Entity.h"

#include "Common.h"

Entity::Entity(const size_t id, const std::string& tag)
	: m_ID(id)
	, m_tag(tag)
{
}

Entity::~Entity()
{}

void Entity::destroy()
{
	m_alive = false;
}
  
bool Entity::isTag(std::string tag)
{
  return (m_tag == tag);
}
