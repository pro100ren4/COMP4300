#pragma once

#include <memory>
#include <string>

#include "Components.h"
#include "Common.h"

class Entity
{
  friend class EntityManager;

  bool m_alive = true;
  size_t m_ID = 0;
  std::string m_tag = "default";


public:
  // HACK: Конструкторы и деструктор должны быть приватными, но компилятор 
  //       решил повыебываться, поэтому, теперь они публичные. Но надо теперь
  //       следить, что сущности создаются только с помощью менеджера сущностей
  Entity() {}
  Entity(const size_t id, const std::string &tag);
  ~Entity();

  std::shared_ptr<CTransform> transform;
  std::shared_ptr<CBoundingBox> boundingBox;
  std::shared_ptr<CInput> input;
  std::shared_ptr<CTimer> timer;

  void destroy();
  bool isTag(std::string tag);
};

