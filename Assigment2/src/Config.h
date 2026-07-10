#pragma once

#include <string>

#include <raylib.h>

struct WindowConfig 
{
  size_t width;
  size_t height;
  float FPSLimit;
  bool isFullScreen;
};

struct FontConfig
{
  std::string name;
  size_t size;
  Color color;
};

struct PlayerConfig
{
  int shapeRadius;
  int collisionRadius;
  float speed;
  Color fillColor;
  Color outlineColor;
  int sidesNumber;
};

struct EnemyConfig
{
  int shapeRadius;
  int collisionRadius;
  float minSpeed;
  float maxSpeed;
  Color outlineColor;
  int outlineThickness;
  int minSidesNumber;
  int maxSidesNumber;
  int particleLifetime;
};

struct BulletConfig
{
  int shapeRadius;
  int collisionRadius;
  float speed;
  Color fillColor;
  Color outlineColor;
  int outlineThickness;
  int sidesNumber;
  int bulletLifetime;
};

struct Config
{
  WindowConfig window;
  FontConfig font;
  PlayerConfig player;
  EnemyConfig enemy;
  BulletConfig bullet;
};
