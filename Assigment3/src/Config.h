#pragma once

#include <map>
#include <vector>
#include <string>

#include <raylib.h>

struct AnimationConfig
{
  std::string texturePath;
  int frameCount;
  int frameTransitionDuration; // Кол-во ИГРОВЫХ кадоров необходимых для 
                               // перехода от одного кадра АНИМАЦИИ к другому
};

struct FontConfig
{
  std::string fontPath; 
  int fontSize;
};

struct TileConfig
{
  std::string name;
  Vector2 position;
};

struct DecConfig
{
  std::string name;
  Vector2 position;
};

struct PlayerConfig
{
  Vector2 position;
  Vector2 aabbSize;
  float moveSpeed;
  float jumpSpeed;
  float gravity;
  std::string bulletAnimationName;
};

struct LevelConfig
{
  std::string levelPath;
  PlayerConfig player;
  std::vector<TileConfig> tiles;
  std::vector<DecConfig> decorations;
};

struct WindowConfig
{
  Vector2 size;
  int targetFps;
};

struct Config
{
  WindowConfig window;
  std::map<std::string, std::shared_ptr<LevelConfig>> level;
  std::map<std::string, AnimationConfig> animation;
  std::map<std::string, FontConfig> font;
};
