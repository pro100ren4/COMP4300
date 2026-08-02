#pragma once

#include <map>
#include <string>

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
};

struct Config
{
  std::map<std::string, AnimationConfig> animation;
  std::map<std::string, FontConfig> font;
};
