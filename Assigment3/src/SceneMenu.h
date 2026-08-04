#pragma once

#include "Scene.h"

class SceneMenu : public Scene
{
  std::vector<std::string> m_menuEntries;
  int m_selectedEntry = 0;
  Font m_primaryFont;
  float m_primaryFontSize;
  Color m_primaryFontColor;
  Color m_primaryFontAccent;
  Color m_backgroundColor;
  Color m_primaryFontSelected;

  void drawMenuEntry(int numEntry);

public:
  SceneMenu();
  ~SceneMenu();

  void systemInput()  override;
  void systemUpdate() override;
  void systemRender() override;
};
