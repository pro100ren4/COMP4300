#pragma once

#include "Scene.h"

class SceneLevel : public Scene
{


public:
  SceneLevel();
  ~SceneLevel();

  void systemInput()  override;
  void systemUpdate() override;
  void systemRender() override;
};
