#pragma once

#include "Scene.h"

class GameEngine
{
  std::map<std::string, std::shared_ptr<Scene>> m_scenes;
  AssetManager m_assetManager;

  std::string m_currentScene;
  bool m_running = false;

public:
  GameEngine();
  ~GameEngine();

  bool isRunning() { return m_running; }
  std::string getCurrentScene() { return m_currentScene; }

  void initialize();
  void quit();
  void run();

  Asset &getAsset(std::string name);
};

GameEngine G;
