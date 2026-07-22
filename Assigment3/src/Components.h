#pragma once

#include <raylib.h>

#include "Vec2.h"

class CTransform
{
public:
    Vector2 position;
    Vector2 velocity;
    float angle;
  
    CTransform(const Vector2 &position, const Vector2 &velocity, float angle)
        : position(position)
        , velocity(velocity)
        , angle(angle)
    {}
};

class CTexture
{
public:
  Texture2D texture;
  Rectangle rectangle;
  Color tint;

  CTexture(Texture2D texture, Rectangle rectangle, Color tint)
    : texture(texture)
    , rectangle(rectangle)
    , tint(tint)
  {}
};

class CAnimation
{
public:
  std::string name;
  Texture2D animationTileset;
  int numberFrames;
  int currentFrame;
  int transitionTimeInFrames;
  Vector2 sizeOfFrame;

  CAnimation(
      std::string name,
      Texture2D animationTileset,
      int numberFrames,
      int transitionTimeInFrames,
      Vector sizeOfFrame)
    : name(name)
    , animationTileset(animationTileset)
    , numberFrames(numberFrames)
    , currentFrame(0)
    , transitionTimeInFrames(transitionTimeInFrames)
    , sizeOfFrame(sizeOfFrame)
};

class CBoundingBox
{
public:
    Vector2 size; 

    CBoundingBox(size)
        : size(size)
    {}
};

class CInput
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false; 

    CInput();
};

class CTimer
{
public:
    size_t totalCount;
    size_t currentCount;
    
    CTimer(size_t count)
        : totalCount(count)
        , currentCount(count)
    {}
};
