#include "GameEngine.h"

#include <iostream>
#include <fstream>

#include <raylib.h>

#include "SceneMenu.h"
#include "SceneLevel.h"
#include "Config.h"
#include "Common.h"

GameEngine G;

void GameEngine::loadConfig(std::string configPath)
{
  std::ifstream configFile(configPath); 
  if (!configFile.is_open()) {
    WARN("Failed to open file: %s", configPath.c_str());
    return;
  }

  std::string classifier;
  while (configFile >> classifier)
  {
    if (classifier == "Window")
    {
      configFile >> m_config.window.size.x;
      configFile >> m_config.window.size.y;
      configFile >> m_config.window.targetFps;
    }
    else if (classifier == "Assets")
    { 
      std::string assetsPath;
      configFile >> assetsPath;
      loadAssetConfig(m_basePath + assetsPath);
    }
    else if (classifier == "Level")
    {
      std::string levelName;
      std::string levelPath;

      configFile >> levelName;
      configFile >> levelPath;

      loadLevelConfig(levelName, m_basePath + levelPath);
    }
  }
}

void GameEngine::loadAssetConfig(std::string assetConfigPath)
{  
  std::ifstream configFile(assetConfigPath);
  if (!configFile.is_open()) {
    WARN("Failed to open file: %s", assetConfigPath.c_str());
    return;
  }


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

void GameEngine::loadLevelConfig(std::string name, std::string levelConfigPath)
{  
  std::ifstream configFile(levelConfigPath); 
  if (!configFile.is_open()) {
    WARN("Failed to open file: %s", levelConfigPath.c_str());
    return;
  }

  std::shared_ptr<LevelConfig> lconfig = std::make_shared<LevelConfig>();
  lconfig->levelPath = levelConfigPath;

  std::string classifier;
  while (configFile >> classifier)
  {
    if (classifier == "Tile")
    {
      TileConfig tconfig;
      configFile >> tconfig.name;
      configFile >> tconfig.position.x;
      configFile >> tconfig.position.y;

      lconfig->tiles.push_back(tconfig);
    }
    else if (classifier == "Dec")
    { 
      DecConfig dconfig;
      configFile >> dconfig.name;
      configFile >> dconfig.position.x;
      configFile >> dconfig.position.y;

      lconfig->decorations.push_back(dconfig);
    }
    else if (classifier == "Player")
    {
      configFile >> lconfig->player.position.x;
      configFile >> lconfig->player.position.y;
      configFile >> lconfig->player.aabbSize.x;
      configFile >> lconfig->player.aabbSize.y;
      configFile >> lconfig->player.moveSpeed;
      configFile >> lconfig->player.jumpSpeed;
      configFile >> lconfig->player.gravity;
      configFile >> lconfig->player.bulletAnimationName;
    }
  }

  m_config.level[name] = lconfig;
}

GameEngine::GameEngine()
{
  m_basePath = GetApplicationDirectory();
#ifdef NDEBUG
  SetTraceLogLevel(LOG_WARNING);
#endif

  loadConfig(m_basePath + "res/config.txt");

  InitWindow(
      m_config.window.size.x,
      m_config.window.size.y,
      "Super MEGA MARIO");
  SetExitKey(KEY_NULL); // Отключить выход по нажатию ESC 
  SetTargetFPS(m_config.window.targetFps);
  
  loadAssets();


  m_scenes["Menu"] = std::make_shared<SceneMenu>();
  for (const auto &it: m_config.level)
  { 
    m_scenes[it.first] = std::make_shared<SceneLevel>(it.second);
  }

  setCurrentScene("Menu");


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
    Texture2D texture = LoadTextureFromImage(LoadImage(texturePath.c_str()));
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

Texture2D GameEngine::getTexture(std::string name)
{
  return m_textures[name];
}

Font GameEngine::getFont(std::string name)
{
  return m_fonts[name];
}

void GameEngine::exit()
{
  m_running = false;
}
