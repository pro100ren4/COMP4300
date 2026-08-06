#pragma once

#include <raylib.h>

#include "Common.h"

class CTransform
{
public:
    Vector2 prevPosition;
    Vector2 position; // NOTE: Должен быть в пикселях экрана. Так сильно прище
    Vector2 velocity;
    float angle;
  
    CTransform(const Vector2 &position, const Vector2 &velocity, float angle)
        : prevPosition(position)
        , position(position)
        , velocity(velocity)
        , angle(angle)
    {}
};

class CAnimation
{
public:
  Texture2D animationTileset;
  int numberFrames;
  int currentFrame;
  int transitionTimeInFrames;
  Vector2 sizeOfFrame;
  bool isPlaying = false;

  CAnimation(
      Texture2D animationTileset,
      int numberFrames,
      int transitionTimeInFrames,
      Vector2 sizeOfFrame)
    : animationTileset(animationTileset)
    , numberFrames(numberFrames)
    , currentFrame(0)
    , transitionTimeInFrames(transitionTimeInFrames)
    , sizeOfFrame(sizeOfFrame)
  {}
};

class CBoundingBox
{
public:
    Vector2 size; 

    CBoundingBox(Vector2 size)
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

    CInput() {};
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
