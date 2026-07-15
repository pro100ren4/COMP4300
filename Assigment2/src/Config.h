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
  float thickness;
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
  int spawnInterval;
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
  bool isConfigValid = false;

  WindowConfig window;
  FontConfig font;
  PlayerConfig player;
  EnemyConfig enemy;
  BulletConfig bullet;
};
