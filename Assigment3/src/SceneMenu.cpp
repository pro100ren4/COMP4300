#include "SceneMenu.h"

#include <raylib.h>

#include "GameEngine.h"
#include "Common.h"

#define EXIT "Exit"

SceneMenu::SceneMenu()
{ 
  m_primaryFont = G.getFont("Beholden");
  m_primaryFontSize = 32.f;

  textColors[PRIMARY]        = GetColor(0xFFFFFFFF);
  textColors[PRIMARY_ACCENT] = GetColor(0xFBD133FF);
  textColors[BACKGROUND]     = GetColor(0x8BC1E8FF);
  textColors[SELECTED]       = GetColor(0xFFAA64FF);

  for (const auto &it: G.m_config.level)
    m_menuEntries.push_back(it.first);

  m_menuEntries.push_back("Settings");
  m_menuEntries.push_back(EXIT);
}

SceneMenu::~SceneMenu()
{
  m_menuEntries.clear();
}

void SceneMenu::drawMenuEntry(int numEntry)
{

  Vector2 textSize = MeasureTextEx(
      m_primaryFont, 
      m_menuEntries[numEntry].c_str(),
      m_primaryFont.baseSize,
      1.f);

  Vector2 windowSize {};
  windowSize.x = GetRenderWidth();
  windowSize.y = GetRenderHeight();

  Vector2 textPos {};
  textPos.x = (windowSize.x / 2) - (textSize.x / 2);
  textPos.y = (0.15f * windowSize.y) + numEntry * (m_primaryFont.baseSize + 10);

  Vector2 accentPos {};
  accentPos.x = textPos.x + 2;
  accentPos.y = textPos.y + 2;


  if (numEntry == m_selectedEntry)
  {
    DrawTextEx(
        m_primaryFont,
        m_menuEntries[numEntry].c_str(),
        accentPos,
        m_primaryFont.baseSize,
        1.f,
        textColors[PRIMARY_ACCENT]);
    DrawTextEx(
        m_primaryFont,
        m_menuEntries[numEntry].c_str(),
        textPos,
        m_primaryFont.baseSize,
        1.f,
        textColors[SELECTED]);
  } 
  else
  {  
    DrawTextEx(
        m_primaryFont,
        m_menuEntries[numEntry].c_str(),
        accentPos,
        m_primaryFont.baseSize,
        1.f,
        textColors[PRIMARY_ACCENT]);

    DrawTextEx(
        m_primaryFont,
        m_menuEntries[numEntry].c_str(),
        textPos,
        m_primaryFont.baseSize,
        1.f,
        textColors[PRIMARY]);
  }

}

void SceneMenu::systemInput()
{
  if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
  {
    m_selectedEntry = (m_selectedEntry + 1);
    
    if (m_selectedEntry >= m_menuEntries.size())
      m_selectedEntry = 0;
  }
  else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
  {
    m_selectedEntry = (m_selectedEntry - 1);
    
    if (m_selectedEntry < 0)
      m_selectedEntry = m_menuEntries.size() - 1;
  }
  else if (IsKeyPressed(KEY_ENTER))
  {
    
    for (const auto &it: G.m_config.level)
    {
      if (it.first == m_menuEntries[m_selectedEntry])
        G.setCurrentScene(it.first);
    }

    if (m_menuEntries[m_selectedEntry] == EXIT)
      G.exit();
  }
}

void SceneMenu::systemUpdate()
{}

void SceneMenu::systemRender()
{
  BeginDrawing();

  ClearBackground(textColors[BACKGROUND]);

  for (int i = 0; i < m_menuEntries.size(); i++)
  {
    drawMenuEntry(i);
  }

  
  EndDrawing();
}
