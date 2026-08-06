#include "SceneLevel.h"

#include <string>
#include <cmath>

#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

#include "Components.h"
#include "GameEngine.h"

// TODO:
// * Обработку столкновений
// * Движение игрока

void SceneLevel::createTile(const TileConfig &c)
{
  auto tile = m_entities.addEntity("Tile");

  /* TRANSFORM */
  Vector2 tilePosition 
    = Vector2Scale(c.position, static_cast<float>(m_tileWidth));
  Vector2 tileVelocity {}; // У тайла нулевая скорость
  float tileAngle = 0.f;

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
  tileSize.y = static_cast<float>(tileAnimTileset.height);
  tileSize.x = static_cast<float>(tileAnimTileset.width / tileNumberFrames);

  tile->animation = std::make_shared<CAnimation>(
      tileAnimTileset,
      tileNumberFrames,
      tileTransitionTimeInFrames,
      tileSize);

  /* BOUNDING BOX */
  tile->aabb = std::make_shared<CBoundingBox>(tileSize);
}

void SceneLevel::createDecoration(const DecConfig &c)
{
  auto decoration = m_entities.addEntity("Decoration");

  /* TRANSFORM */
  // Vector2 decorationPosition = c.position;
  Vector2 decorationPosition 
    = Vector2Scale(c.position, static_cast<float>(m_tileWidth));
  Vector2 decorationVelocity {}; // У тайла нулевая скорость
  float decorationAngle = 0.f;

  decoration->transform = std::make_shared<CTransform>(
      decorationPosition,
      decorationVelocity,
      decorationAngle);

  /* ANIMATION */
  Texture2D decorationAnimTileset = G.getTexture(c.name);
  int decorationNumberFrames = G.m_config.animation[c.name].frameCount;
  int decorationTransitionTimeInFrames = 
    G.m_config.animation[c.name].frameTransitionDuration;
  Vector2 decorationSize {};
  decorationSize.y = static_cast<float>(decorationAnimTileset.height);
  decorationSize.x = static_cast<float>(decorationAnimTileset.width / decorationNumberFrames);

  decoration->animation = std::make_shared<CAnimation>(
      decorationAnimTileset,
      decorationNumberFrames,
      decorationTransitionTimeInFrames,
      decorationSize);
}

void SceneLevel::createPlayer(const PlayerConfig &c)
{
  m_player = m_entities.addEntity("Player");

  /* TRANSFORM */
  // Vector2 playerPos = c.position;
  Vector2 playerPos 
    = Vector2Scale(c.position, static_cast<float>(m_tileWidth));
  Vector2 playerVel {};
  float   playerAngle = 0.f;

  m_player->transform = std::make_shared<CTransform>(
      playerPos, playerVel, playerAngle);

  /* ANIMATION */
  Texture2D playerTileset = G.getTexture("Stand");
  int playerTilesetNumFrames 
    = G.m_config.animation["Stand"].frameCount;
  int playerTransitionTime 
    = G.m_config.animation["Stand"].frameTransitionDuration;
  Vector2 playerFrameSize;
  playerFrameSize.y = static_cast<float>(playerTileset.height);
  playerFrameSize.x = static_cast<float>(playerTileset.width / playerTilesetNumFrames);

  m_player->animation = std::make_shared<CAnimation>(
      playerTileset,
      playerTilesetNumFrames,
      playerTransitionTime,
      playerFrameSize);

  /* BOUNDING BOX */
  m_player->aabb = std::make_shared<CBoundingBox>(playerFrameSize);

  m_player->input = std::make_shared<CInput>();
}

void SceneLevel::drawEntities()
{  
  auto entities = m_entities.getEntities(); 
  for (const auto &e: entities)
  {
    if (!e->transform || !e->animation)
      continue;
    
    Texture2D tileTexture = e->animation->animationTileset;
      
    Rectangle tileRect {};
    tileRect.x = e->animation->currentFrame * e->animation->sizeOfFrame.x;
    tileRect.y = 0;
    tileRect.width = e->animation->sizeOfFrame.x;
    tileRect.height = e->animation->sizeOfFrame.y;
    Vector2 tilePos = e->transform->position;
      // Vector2Scale(e->transform->position, static_cast<float>(m_tileWidth));

    DrawTextureRec(tileTexture, tileRect, tilePos, WHITE);
  }
}

void SceneLevel::DEBUG_drawGrid()
{
  for (int y = 0; y < G.m_config.window.size.y; y += m_tileHeight)
  {
    DrawLine(0, y, static_cast<int>(G.m_config.window.size.x), y, WHITE);
    std::string cellCoord = std::to_string(y / m_tileHeight);
    DrawText(cellCoord.c_str(), 2, y + 2, 10, WHITE);
  }

  for (int x = 0; x < G.m_config.window.size.x; x += m_tileWidth)
  {
    DrawLine(x, 0, x, static_cast<int>(G.m_config.window.size.y), WHITE);
    std::string cellCoord = std::to_string(x / m_tileWidth);
    DrawText(cellCoord.c_str(), x + 2, 2, 10, WHITE);
  }

  Vector2 mousePos = GetMousePosition(); 

  DrawLine(
      0                           , static_cast<int>(mousePos.y+1),
      static_cast<int>(mousePos.x), static_cast<int>(mousePos.y+1),
      BLACK);
  DrawLine(
      0                           , static_cast<int>(mousePos.y),
      static_cast<int>(mousePos.x), static_cast<int>(mousePos.y),
      RED);

  DrawLine(
      static_cast<int>(mousePos.x+1), 0,
      static_cast<int>(mousePos.x+1), static_cast<int>(mousePos.y),
      BLACK);

  DrawLine(
      static_cast<int>(mousePos.x), 0,
      static_cast<int>(mousePos.x), static_cast<int>(mousePos.y),
      RED);

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

void SceneLevel::DEBUG_drawAABB()
{
  auto entities = m_entities.getEntities();

  for (const auto &e: entities)
  {
    if (!e->aabb || !e->transform)
      continue;

    Rectangle rec;
    rec.x      = e->transform->position.x; //* m_tileWidth;
    rec.y      = e->transform->position.y; //* m_tileHeight;
    rec.width  = e->aabb->size.x;
    rec.height = e->aabb->size.y;

    DrawRectangleLinesEx(rec, 1.2f, GetColor(0xFF00FFFF));
  }
}

void SceneLevel::DEBUG_drawInfo()
{
  Font beholden = G.getFont("Beholden");

  int fps = GetFPS();
  std::string info = "FPS " + std::to_string(fps);

  Vector2 infoPos {};
  infoPos.x = 6;
  infoPos.y = 6;

  DrawTextEx(beholden, info.c_str(), infoPos, 18.f, 1.f, BLACK);   

  infoPos.x -= 1;
  infoPos.y -= 1;

  DrawTextEx(beholden, info.c_str(), infoPos, 18.f, 1.f, GREEN);   
}

void SceneLevel::systemAnimation()
{
  auto entities = m_entities.getEntities();

  for (const auto &e: entities)
  {
    if ((!e->animation) ||
        (!e->animation->isPlaying))
      continue;
       

    // NOTE: Если "длительность" анимации 0, но она помечена как запущенная, то
    //       отключаем ее. Для каждого тайла, у которого нету анимации, это
    //       условие должно выполнятся только один раз. Только если не запусть
    //       анимацию для тайлов снова.
    if (e->animation->isPlaying && e->animation->transitionTimeInFrames == 0)
    {
      e->animation->isPlaying = false;
    }


    if (G.currentFrame % e->animation->transitionTimeInFrames == 0)
    {
      e->animation->currentFrame 
        = (e->animation->currentFrame + 1) % e->animation->numberFrames;
    }

  }
}

Vector2 SceneLevel::getOverlap(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
{
  Vector2 result {};

  if ((!e1->transform) || (!e1->aabb) ||
      (!e2->transform) || (!e1->aabb))
  {
    return result;
  }

  float dx = fabs((e2->transform->position.x + e2->aabb->size.x / 2) -
                  (e1->transform->position.x + e1->aabb->size.x / 2));
  float dy = fabs((e2->transform->position.y + e2->aabb->size.y / 2) -
                  (e1->transform->position.y + e1->aabb->size.y / 2));

  result.x = (e2->aabb->size.x + e1->aabb->size.x) / 2 - dx;
  result.y = (e2->aabb->size.y + e1->aabb->size.y) / 2 - dy;
  
  return result;
}

void SceneLevel::systemPhysics()
{
  auto entities = m_entities.getEntities("Tile");

  for ( const auto &e: entities)
  {
    if (!e->aabb || !e->transform)
      continue;
    
    Vector2 overlap = getOverlap(m_player, e);
    
    if (overlap.x > 0.f && overlap.y > 0.f)
    {
      // TODO: Надо каким-то образом определить положение игрока, если игрок
      // находиться над тайлом и произошла коллизия, значит он стоит.
      //
      // TODO: Определение разрешения коллизии проиходит на основании предыду-
      //       щего пололжения. При возникновении коллизии надо проверить
      //       какое было перекрытие на прошлом кадре и разрешить коллизию
      //       основываясь на этом. Если было горизонтальное перекрытие, то
      //       движение было вертикальным.
      
      TODO("Collision");
      
    }
  }
}

void SceneLevel::systemMovement()
{
  m_player->transform->velocity.y = 0;
  m_player->transform->velocity.x = 0;

  if (m_player->input->up)
    m_player->transform->velocity.y = -1;
  if (m_player->input->down)
    m_player->transform->velocity.y = +1;
  if (m_player->input->left)
    m_player->transform->velocity.x = -1;
  if (m_player->input->right)
    m_player->transform->velocity.x = +1;

  auto entities = m_entities.getEntities(); 

  for (const auto &e: entities)
  {
    e->transform->position = Vector2Add(e->transform->position, 
        Vector2Normalize(e->transform->velocity));
  }
}

SceneLevel::SceneLevel(std::shared_ptr<LevelConfig> levelConfig)
  : m_levelConfig(levelConfig)
{

#ifndef NDEBUG
  m_displayGrid = true;
  m_displayAABB = true;
#endif

  for (const auto &it: m_levelConfig->tiles)
  {
    createTile(it);
  }

  for (const auto &it: m_levelConfig->decorations)
  {
    createDecoration(it);
  }

  createPlayer(levelConfig->player);
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

  if (IsKeyPressed(KEY_ESCAPE))
    G.setCurrentScene("Menu");


  m_player->input->up = false;
  m_player->input->down = false;
  m_player->input->left = false;
  m_player->input->right = false;

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    m_player->input->up = true;
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    m_player->input->down = true;
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    m_player->input->right = true;
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    m_player->input->left = true;

  // if (IsKeyPressed(KEY_P))
  // {
  //   auto entities = m_entities.getEntities();
  //
  //   for (const auto &e: entities)
  //   {
  //     if (e->animation)
  //       e->animation->isPlaying = !e->animation->isPlaying;
  //   }   
  // }
}

void SceneLevel::systemUpdate()
{
  systemMovement();
  systemPhysics();
  systemAnimation();


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
  {
    // drawTiles();
    // drawDecorations();
    drawEntities();
  }
    
  if (m_displayGrid)
    DEBUG_drawGrid();
  if (m_displayAABB)
    DEBUG_drawAABB();
#ifndef NDEBUG
  DEBUG_drawInfo(); 
#endif


  EndDrawing();
}

