#include "SceneMenu.h"

#include <raylib.h>

#include "GameEngine.h"
#include "Common.h"

SceneMenu::SceneMenu()
{ 
  m_primaryFont = G.getFont("Beholden");
  m_primaryFontSize = 32.f;

  m_primaryFontColor.r = 0xFF;
  m_primaryFontColor.g = 0xFF;
  m_primaryFontColor.b = 0xFF;
  m_primaryFontColor.a = 0xFF;

  m_primaryFontAccent.r = 251;
  m_primaryFontAccent.g = 209;
  m_primaryFontAccent.b = 51;
  m_primaryFontAccent.a = 0xFF;

  m_backgroundColor.r = 139;
  m_backgroundColor.g = 193;
  m_backgroundColor.b = 232;
  m_backgroundColor.a = 0xFF;


  m_primaryFontSelected.r = 0xFF;
  m_primaryFontSelected.g = 0xAA;
  m_primaryFontSelected.b = 0x64;
  m_primaryFontSelected.a = 0xFF;

  m_menuEntries.push_back("Play");
  m_menuEntries.push_back("Exit");
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
        m_primaryFontAccent);

    DrawTextEx(
        m_primaryFont,
        m_menuEntries[numEntry].c_str(),
        textPos,
        m_primaryFont.baseSize,
        1.f,
        m_primaryFontSelected);
  } 
  else
  {  
    DrawTextEx(
        m_primaryFont,
        m_menuEntries[numEntry].c_str(),
        accentPos,
        m_primaryFont.baseSize,
        1.f,
        m_primaryFontAccent);

    DrawTextEx(
        m_primaryFont,
        m_menuEntries[numEntry].c_str(),
        textPos,
        m_primaryFont.baseSize,
        1.f,
        m_primaryFontColor);
  }

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

  ClearBackground(m_backgroundColor);

  for (int i = 0; i < m_menuEntries.size(); i++)
  {
    drawMenuEntry(i);
  }

  
  EndDrawing();
}
