#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <raylib.h>

#include "Scene.h"
#include "Config.h"
#include "Common.h"

class Scene;

class GameEngine
{
  bool m_running = false;
  std::map<std::string, std::shared_ptr<Scene>> m_scenes;
  std::string m_currentScene;
  Config m_config; 
  std::string m_basePath;

  std::map<std::string, Image> m_textures;
  std::map<std::string, Font> m_fonts;
  
  void loadConfig(std::string configPath);
  void loadAssets();

public:
  // NOTE: Архитерктурно как будто лучше если у всех сцен будет единый счетчик
  //       кадров, кот. храниться в движке. НО это может быть медленно(?), т.к.
  //       сцене приходиться не просто брать свое локальное поле, а обращаться
  //       к глобальному классу движка.
  int64_t currentFrame = 0;

  GameEngine();
  ~GameEngine();

  void run();

  void setCurrentScene(std::string name);
  void registerAction(KeyboardKey key, const std::string &type);
  std::shared_ptr<Scene> currentScene();

  Image getTexture(std::string name);
  Font getFont(std::string name);
};

// NOTE: Возможно лучше было бы заменить глоабльную переменную на "одиночку"
//       (паттерн), чтобы удостовериться, что каждый экземпляр Scene обращается
//       к одному и тому же экземеляру класса движка, но это может быть медлен-
//       но из-за косвенного обращения к классу.
extern GameEngine G;
