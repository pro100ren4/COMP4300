#include "SceneLevel.h"

#include <raylib.h>

SceneLevel::SceneLevel()
{
}

SceneLevel::~SceneLevel()
{
}

void SceneLevel::systemInput()
{
}

void SceneLevel::systemUpdate()
{
}

void SceneLevel::systemRender()
{
  BeginDrawing();

  ClearBackground(GREEN);

  EndDrawing();
}

