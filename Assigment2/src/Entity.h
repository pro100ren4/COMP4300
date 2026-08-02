#pragma once

#include <string>
#include <memory>
#include <map>

#include "Components.h"

class Entity
{
  friend class EntityManager;

  bool m_alive = true;
  size_t m_ID = 0;
  std::string m_tag = "default";

  Entity() {}
  Entity(const size_t id, const std::string &tag);
  ~Entity();

public:
  std::shared_ptr<CTransform> transform;
  std::shared_ptr<CTexture> texture;
  std::map<std::string, std::shared_ptr<CAnimation>> animations;
  std::shared_ptr<CBoundingBox> boundingBox;
  std::shared_ptr<CInput> input;
  std::shared_ptr<CTimer> timer;

  void destroy();
  bool isTag(std::string tag);
};

