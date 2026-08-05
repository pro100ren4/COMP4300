#include "SceneLevel.h"

#include <string>

#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

#include "GameEngine.h"

// TODO:
// * Отрисовки сетку тайлов
// * Обработку ввода пользователя
// * Обработку столкновений
// * Отрисовку коллизий

void SceneLevel::createTile(const TileConfig &c)
{
  /* TRANSFORM */
  Vector2 tilePosition = c.position;
  Vector2 tileVelocity {}; // У тайла нулевая скорость
  float tileAngle = 0.f;

  auto tile = m_entities.addEntity("Tile");
  tile->transform = std::make_shared<CTransform>(
      tilePosition,
      tileVelocity,
      tileAngle);

  /* ANIMATION */
  Texture2D tileAnimTileset = G.getTexture(c.name);
  int tileNumberFrames = G.m_config.animation[c.name].frameCount;
  int tileTransitionTimeInFrames = 
    G.m_config.animation[c.name].frameTransitionDuration;
  Vector2 tileSize {};
  tileSize.y = tileAnimTileset.height;
  tileSize.x = tileAnimTileset.height / tileNumberFrames;

  tile->animation = std::make_shared<CAnimation>(
      tileAnimTileset,
      tileNumberFrames,
      tileTransitionTimeInFrames,
      tileSize);

  /* BOUNDING BOX */
  tile->aabb = std::make_shared<CBoundingBox>(tileSize);
}

void SceneLevel::drawTiles()
{
  auto entities = m_entities.getEntities(); 
  for (const auto &e: entities)
  {
    if (!e->transform || !e->animation)
      continue;
    
    // DrawRectangleV( e->transform->position, e->animation->sizeOfFrame, RED);
    Texture2D tileTexture = e->animation->animationTileset;
      
    Rectangle tileRect {};
    tileRect.x = e->animation->currentFrame * e->animation->sizeOfFrame.x;
    tileRect.y = 0;
    tileRect.width = e->animation->sizeOfFrame.x;
    tileRect.height = e->animation->sizeOfFrame.y;
    Vector2 tilePos = 
      Vector2Multiply(e->transform->position, e->animation->sizeOfFrame);

    DrawTextureRec(tileTexture, tileRect, tilePos, WHITE);
  }
}

void SceneLevel::drawGrid()
{
  for (int y = 0; y < G.m_config.window.size.y; y += m_tileHeight)
  {
    DrawLine(0, y, G.m_config.window.size.x, y, WHITE);
    std::string cellCoord = std::to_string(y / m_tileHeight);
    DrawText(cellCoord.c_str(), 2, y + 2, 10, WHITE);
  }

  for (int x = 0; x < G.m_config.window.size.x; x += m_tileWidth)
  {
    DrawLine(x, 0, x, G.m_config.window.size.y, WHITE);
    std::string cellCoord = std::to_string(x / m_tileWidth);
    DrawText(cellCoord.c_str(), x + 2, 2, 10, WHITE);
  }

  Vector2 mousePos = GetMousePosition(); 

  DrawLine(0, mousePos.y+1, mousePos.x, mousePos.y+1, BLACK);
  DrawLine(0, mousePos.y, mousePos.x, mousePos.y, RED);

  DrawLine(mousePos.x+1, 0, mousePos.x+1, mousePos.y, BLACK);
  DrawLine(mousePos.x, 0, mousePos.x, mousePos.y, RED);

  std::string cellMouseCoord = 
    std::to_string(static_cast<int>(mousePos.x / m_tileWidth)) 
    + "," + 
    std::to_string(static_cast<int>(mousePos.y / m_tileHeight));
  Font font = G.getFont("Beholden");

  Vector2 coordTextSize = MeasureTextEx(font, cellMouseCoord.c_str(), 20.f, 1.f);

  Vector2 textOffset {};
  if (G.m_config.window.size.x * 0.05 > mousePos.x)
    textOffset.x = 0;
  else
    textOffset.x = -coordTextSize.x;

  if (G.m_config.window.size.y * 0.05 > mousePos.y)
    textOffset.y = 0;
  else 
    textOffset.y = -coordTextSize.y;

  DrawTextEx(
      font,
      cellMouseCoord.c_str(),
      Vector2Add(mousePos, textOffset),
      20.f, 1.f,
      BLACK);

  DrawTextEx(
      font,
      cellMouseCoord.c_str(),
      Vector2Add(mousePos, textOffset),
      21.f, 1.f,
      WHITE);
}

void SceneLevel::dradAABB()
{
  auto entities = m_entities.getEntities();

  for (const auto &e: entitites)
  {
    if (!e->boundingBox || !e->transform)
      continue;

    DrawRecta
  }
}

SceneLevel::SceneLevel(std::shared_ptr<LevelConfig> levelConfig)
  : m_levelConfig(levelConfig)
{
  for (const auto &it: m_levelConfig->tiles)
  {
    createTile(it);
  }
}

SceneLevel::~SceneLevel()
{
}

void SceneLevel::systemInput()
{
  if (IsKeyPressed(KEY_G))
    m_displayGrid = !m_displayGrid;

  if (IsKeyPressed(KEY_B))
    m_displayAABB = !m_displayAABB;

  if (IsKeyPressed(KEY_H))
    m_displaySprites = !m_displaySprites;
}

void SceneLevel::systemUpdate()
{
  m_entities.update();
}

void SceneLevel::systemRender()
{

  // TODO: В дальнейшем следуем заменить на BeginMode2D и EndMode2D с Camera2D
  //       для поддержки уровней выходящих за границы экрана.
  BeginDrawing();

  // Зафиксировать цвет фона в будущем
  ClearBackground(BLUE);

  if (m_displaySprites)
    drawTiles();
  if (m_displayGrid)
    drawGrid();

  EndDrawing();
}

