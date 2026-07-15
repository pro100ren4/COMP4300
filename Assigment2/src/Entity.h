#pragma once

#include <string>
#include <memory>

#include "Components.h"

class Entity
{
  friend class EntityManager;

  bool m_alive = true;
  size_t m_ID = 0;
  std::string m_tag = "default";

  Entity() {}
  Entity(const size_t id, const std::string &tag);

public:
  std::shared_ptr<CTransform> transform;
  std::shared_ptr<CShape> shape;
  std::shared_ptr<CCollision> collision;
  std::shared_ptr<CScore> score;
  std::shared_ptr<CInput> input;
  std::shared_ptr<CTimer> timer;

  void destroy();
};

