#pragma once

#include <raylib.h>

#include "Vec2.h"

class CTransform
{
public:
    Vec2 position;
    Vec2 velocity;
    float angle;
  
    CTransform(const Vec2 &position, const Vec2 &velocity, float angle)
        : position(position)
        , velocity(velocity)
        , angle(angle)
    {}
};

class CShape
{
public:
    size_t numberVerticies;
    Color outline;
    Color fill;
    float thickness;
    float radius;

    CShape(const size_t numberVerticies, const Color& outline, const Color& fill, float thickness, float radius)
        : numberVerticies(numberVerticies)
        , outline(outline)
        , fill(fill)
        , thickness(thickness)
        , radius(radius)
    {}
};

class CCollision
{
public:
    float radius = 0.f;

    CCollision(float radius)
        : radius(radius)
    {}
};

class CScore
{
public:
    int score = 0;

    CScore(int score)
      : score(score)
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
    Vec2 shootTarget;

    CInput()
      : shootTarget(0, 0)
    {}
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
