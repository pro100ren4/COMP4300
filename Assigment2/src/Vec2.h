#pragma once

class Vec2
{
public:
  float x = 0.f;
  float y = 0.f;

  Vec2() {};
  Vec2(float x, float y);
 
  Vec2 operator+(const Vec2 &other);
  Vec2 operator-(const Vec2 &other);
  Vec2 operator*(const Vec2 &other);
  Vec2 operator/(const Vec2 &other);

  void operator+=(const Vec2 &other);
  void operator-=(const Vec2 &other);
  void operator*=(const Vec2 &other);
  void operator/=(const Vec2 &other);

  float distance(const Vec2 &destination);
};

