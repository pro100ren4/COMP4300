#pragma once

#include <raylib.h>

#include "Vec2.h"

class CTransform
{
public:
  Vec2 positon;
  Vec2 velocity;
  float angle;    // NOTE: Need to be explained in which units agnle are.
                  // In radians or in degrees. 
  
  CTransform(const Vec2 &postion, const Vec2 &velocity, float angle)
    : position(position)
    , velocity(velocity)
    , angle(angle)
  {
  }
};

class CInput
{
};

class CTimer
{
};

