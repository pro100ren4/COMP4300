#pragma once

#include <string>
#include <memory>

class Entity
{

  friend class EntityManager;

  bool m_alive = true;
  size_t m_ID = 0;
  std::string m_tag = "default";

  Entity(const size_t id, const std::string &tag);

public:
  // TODO: place a shared pointers to entity components here
};

