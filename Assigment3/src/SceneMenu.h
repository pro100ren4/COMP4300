#pragma once

#include "Scene.h"

class SceneMenu : public Scene
{
  std::vector<std::string> m_menuEntries;

public:
  SceneMenu();
  ~SceneMenu();

  void systemInput()  override;
  void systemUpdate() override;
  void systemRender() override;
};
