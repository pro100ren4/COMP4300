#include "GameEngine.h"

#include <iostream>

#include <raylib.h>

#include "Common.h"


GameEngine::GameEngine()
{
  m_scenes["SceneMenu"] = std::make_shared<Scene>();
  m_scenes["SceneLevel"] = std::make_shared<Scene>();

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

