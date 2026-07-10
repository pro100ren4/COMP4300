#include "Entity.h"

Entity::Entity(const size_t id, const std::string& tag)
	: m_ID(id)
	, m_tag(tag)
{
}

void Entity::destroy()
{
	m_alive = false;
}
