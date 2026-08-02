#pragma once

#include "EntityManager.h"
#include "Common.h"

class Scene
{
  EntityManager m_eneities;

public:
  Scene();
  ~Scene();

  void systemInput();
  void systemUpdate();
  void systemRender();
};
