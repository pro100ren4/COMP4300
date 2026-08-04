#include "GameEngine.h"

#include <iostream>
#include <fstream>

#include <raylib.h>

#include "SceneMenu.h"
#include "Config.h"
#include "Common.h"


void GameEngine::loadConfig(std::string configPath)
{
  std::ifstream configFile(configPath); 

  std::string classifier;
  while (configFile >> classifier)
  {
    if (classifier == "Animation")
    {
      std::string aname;
      AnimationConfig aconfig;
      configFile >> aname;
      configFile >> aconfig.texturePath;
      configFile >> aconfig.frameCount;
      configFile >> aconfig.frameTransitionDuration;

      m_config.animation[aname] = aconfig;
    }
    else if (classifier == "Font")
    { 
      std::string fname;
      FontConfig fconfig;
      configFile >> fname;
      configFile >> fconfig.fontPath;
      configFile >> fconfig.fontSize;

      m_config.font[fname] = fconfig;
    }
  }
}

GameEngine::GameEngine()
{
#ifndef NDEBUG
  SetTraceLogLevel(LOG_WARNING);
#endif

  InitWindow(1280, 720, "Super MEGA MARIO");
  SetExitKey(KEY_NULL); // Отключить выход по нажатию ESC 
  
  m_basePath = GetApplicationDirectory();

  loadConfig(m_basePath + "res/assets.txt");
  loadAssets();

  m_scenes["SceneMenu"] = std::make_shared<SceneMenu>();
  m_scenes["SceneLevel"] = std::make_shared<SceneMenu>();

  setCurrentScene("SceneMenu");


  m_running = true;
}

GameEngine::~GameEngine()
{
  CloseWindow();
}

void GameEngine::run()
{ 
  while(m_running)
  {

    if (WindowShouldClose())
      m_running = false;
        
    currentScene()->systemInput();
    currentScene()->systemUpdate();
    currentScene()->systemRender();

    currentFrame++;
    if (currentFrame < 0) currentFrame = 0;
  }
}

void GameEngine::setCurrentScene(std::string name)
{
  m_currentScene = name;
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
  return m_scenes[m_currentScene];
}

void GameEngine::loadAssets()
{
  for (const auto &it: m_config.animation)
  {
    std::string texturePath = m_basePath + it.second.texturePath;
    Image texture = LoadImage(texturePath.c_str());
    m_textures[it.first] = texture;
  }

  int fontSize = 48;

  for (const auto &it: m_config.font)
  {
    std::string fontPath = m_basePath + it.second.fontPath;
    Font font = LoadFontEx(fontPath.c_str(), it.second.fontSize, nullptr, 0);
    m_fonts[it.first] = font;
  }
}

Image GameEngine::getTexture(std::string name)
{
  return m_textures[name];
}

Font GameEngine::getFont(std::string name)
{
  return m_fonts[name];
}
