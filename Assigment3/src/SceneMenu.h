#pragma once

#include "Scene.h"

class SceneMenu : public Scene
{
  enum ColorType {
    PRIMARY = 0,
    PRIMARY_ACCENT,
    SECONDARY,
    SECONDARY_ACCENT, 
    BACKGROUND,
    SELECTED,
    MAX
  };

  std::vector<std::string> m_menuEntries;
  int m_selectedEntry = 0;
  Font m_primaryFont;
  float m_primaryFontSize;

  Color textColors[ColorType::MAX];

  void drawMenuEntry(int numEntry);

public:
  SceneMenu();
  ~SceneMenu();

  void systemInput()  override;
  void systemUpdate() override;
  void systemRender() override;
};
