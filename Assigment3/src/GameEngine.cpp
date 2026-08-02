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

      m_config.font[fname] = fconfig;
    }
  }
}

GameEngine::GameEngine()
{
  
  std::string basePath(GetApplicationDirectory());

  loadConfig(basePath + "res/assets.txt");

  m_scenes["SceneMenu"] = std::make_shared<SceneMenu>();
  m_scenes["SceneLevel"] = std::make_shared<SceneMenu>();

  setCurrentScene("SceneMenu");

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(1280, 720, "Shity game");
  SetExitKey(KEY_NULL); // Отключить выход по нажатию ESC 

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
        
    m_scenes[m_currentScene]->systemInput();
    m_scenes[m_currentScene]->systemUpdate();
    m_scenes[m_currentScene]->systemRender();

    currentFrame++;
    if (currentFrame < 0) currentFrame = 0;
  }
}

void GameEngine::setCurrentScene(std::string name)
{
  m_currentScene = name;
}

