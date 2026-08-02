#include "SceneMenu.h"

#include <raylib.h>

#include "Common.h"

SceneMenu::SceneMenu()
{ 
  m_menuEntries.push_back("1. Play");
  m_menuEntries.push_back("2. Settings");
  m_menuEntries.push_back("3. Exit");
}

SceneMenu::~SceneMenu()
{
  m_menuEntries.clear();
}

void SceneMenu::systemInput()
{
}

void SceneMenu::systemUpdate()
{
}

void SceneMenu::systemRender()
{
  BeginDrawing();

  ClearBackground(RED);

  EndDrawing();
}
