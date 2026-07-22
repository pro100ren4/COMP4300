#pragma once

#include <string>
#include <map>

struct TextureConfig {
  std::string filePath;
};

struct AnimationConfig
{
  std::string textureName;
  int64_t framesNumber;
  int64_t animationDurationInGameFrames;
};

struct FontConfig
{ 
  std::string filePath;
};

struct AssetsConfig
{
  std::map<std::string, TextureConfig> textures;
  std::map<std::string, AnimationConfig> animations;
  std::map<std::string, FontConfig> fonts;
};
