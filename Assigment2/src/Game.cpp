#include "Game.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include "Config.h"
#include "EntityManager.h"


/******************************************************************************
 * SPAWN FUNCTIONS
 *****************************************************************************/

void Game::spawnPlayer()
{
  m_player = m_manager.addEntity("Player");
  m_player->transform = std::make_shared<CTransform>(
    Vec2(static_cast<float>(m_config.window.width / 2),
         static_cast<float>(m_config.window.height / 2)),
    Vec2(0, 0),
    0.f);
  m_player->shape = std::make_shared<CShape>(
    m_config.player.sidesNumber,
    m_config.player.outlineColor,
    m_config.player.fillColor,
    m_config.player.thickness,
    m_config.player.shapeRadius);

  m_player->collision = std::make_shared<CCollision>(m_config.player.collisionRadius);
  m_player->input = std::make_shared<CInput>();
}

void Game::spawnEnemy()
{

  // TODO: Добавить более привлекательные цвета
  Color enemyColors[] = {
    Color{0xFF, 0xAF, 0xA5, 0xFF},
    Color{0xBF, 0xCF, 0xFF, 0xFF},
    Color{0xC8, 0xE7, 0xED, 0xFF},
    Color{0xFF, 0xFF, 0xC2, 0xFF},
  };

  int enemyNumberSides = rand(m_config.enemy.minSidesNumber, 
                              m_config.enemy.maxSidesNumber);

  Vec2 enemyPosition = Vec2(
    static_cast<float>(rand(0 + m_config.enemy.shapeRadius, m_config.window.width - m_config.enemy.shapeRadius)),
    static_cast<float>(rand(0 + m_config.enemy.shapeRadius, m_config.window.height - m_config.enemy.shapeRadius))
  );

  Vec2 enemyVelocity = Vec2(
    static_cast<float>(rand(m_config.enemy.minSpeed, m_config.enemy.maxSpeed)),
    static_cast<float>(rand(m_config.enemy.minSpeed, m_config.enemy.maxSpeed))
  );

  Color enemyColor = enemyColors[enemyNumberSides % 4];

  auto enemy = m_manager.addEntity("Enemy");
  enemy->transform = std::make_shared<CTransform>(
    enemyPosition,
    enemyVelocity,
    0.f);

  enemy->shape = std::make_shared<CShape>(
    enemyNumberSides,
    m_config.enemy.outlineColor,
    enemyColor,
    m_config.enemy.outlineThickness,
    m_config.enemy.shapeRadius);

  enemy->collision = std::make_shared<CCollision>(
    m_config.enemy.collisionRadius);

  enemy->score = std::make_shared<CScore>(enemyNumberSides * 100);

}

void Game::spawnBullet() {
  auto bullet = m_manager.addEntity("Bullet");

  Vec2 bulletPosition = m_player->transform->position;
  Vec2 bulletVelocity = m_player->input->shootTarget
      - m_player->transform->position;
  bulletVelocity = bulletVelocity.normilize() * m_config.bullet.speed;

  bullet->transform = std::make_shared<CTransform>(
      bulletPosition,
      bulletVelocity,
      0.f);

  bullet->collision = std::make_shared<CCollision>(
      m_config.bullet.collisionRadius);
  
  bullet->shape = std::make_shared<CShape>(
      0,
      m_config.bullet.outlineColor,
      m_config.bullet.fillColor,
      m_config.bullet.outlineThickness,
      m_config.bullet.shapeRadius);

  bullet->timer = std::make_shared<CTimer>(m_config.bullet.bulletLifetime);
}

void Game::spawnGranade()
{
  auto gravityGranade = m_manager.addEntity("GGranade");

  const int granadeLifetime = 60; // Граната существует 2 сек.
  float granadeSpeed = 
    m_player->transform->position
        .distance(m_player->input->specialWeaponTarget)
    / granadeLifetime;

  Vec2 granadePosition = m_player->transform->position;
  Vec2 granadeVelocity = 
    (m_player->input->specialWeaponTarget - m_player->transform->position)
        .normilize()
    * granadeSpeed;

  gravityGranade->transform = std::make_shared<CTransform>(
      granadePosition,
      granadeVelocity,
      0.f);

  gravityGranade->shape = std::make_shared<CShape>(
      0,
      Color {0xFF, 0xFF, 0xFF, 0xFF},
      Color {0x00, 0xFF, 0x00, 0xFF},
      1.f,
      10.f);

  gravityGranade->timer = std::make_shared<CTimer>(granadeLifetime);

  //
  // TODO: При смерти гранаты она должна создавать сущность гравитационной
  // ловушки, которая жила бы секунд 5-10 и притягивала к себе близких врагов.
  // Близких врагов можно определять через distance, а притягивание реализовать
  // либо через прибавление некоторого вектора притяжения к вектору скорости
  // сущности, либо через замену вектора скорости на направелнный в сторону
  // ценкта гравитационной ловушки.
  //
  // Можно реализовать сразу 2 варианта. Если врга далеко, то просто прибавляем
  // , а если близко, то напрявляем прямо в центр.
  // 
}


/******************************************************************************
 * SYSTEMS
 *****************************************************************************/

void Game::systemRender()
{
  drawBackground();

  EntitiesVector entities = m_manager.getEntities();

  for (auto& entity : entities)
  {
    if (entity->shape && entity->transform)
    {
      Vector2 entityPositon = {};
      entityPositon.x = entity->transform->position.x;
      entityPositon.y = entity->transform->position.y;

      if (entity->shape->numberVerticies < 3)
      {
        DrawCircleV(
            entityPositon,
            entity->shape->radius,
            entity->shape->fill);
        DrawCircleLinesV(
            entityPositon,
            entity->shape->radius,
            entity->shape->outline);
      }
      else
      {
        DrawPoly(
          entityPositon,
          static_cast<int>(entity->shape->numberVerticies),
          entity->shape->radius,
          entity->transform->angle,
          entity->shape->fill);
        DrawPolyLinesEx(
          entityPositon,
          static_cast<int>(entity->shape->numberVerticies),
          entity->shape->radius,
          entity->transform->angle,
          entity->shape->thickness,
          entity->shape->outline);
      }
    }
    
    // Drawing Cursor
    if (entity->input)
    {
      float x = entity->input->shootTarget.x;
      float y = entity->input->shootTarget.y;
      DrawRectangle(
          static_cast<int>(x) - 5,
          static_cast<int>(y) - 5,
          10, 10,
          WHITE);
    }

    if (!m_isRunning)
    {
      DrawRectangle(
          0, 0,
          m_config.window.width, m_config.window.height,
          Color{0, 0, 0, 125});
      
      Vector2 textSize = MeasureTextEx(
          m_font, "Pause",
          static_cast<float>(m_config.font.size) * 1.5f, 1.f);

      Vector2 pauseTextPos {
        m_config.window.width / 2 - textSize.x / 2, 
        m_config.window.height / 2 - textSize.y / 2, 
      };

      DrawTextEx(
          m_font,
          "Pause",
          pauseTextPos,
          static_cast<float>(m_config.font.size) * 1.5f,
          1.f,
          m_config.font.color);

    }
  }

  drawScore();
}


void Game::systemMovement()
{
  EntitiesVector entities = m_manager.getEntities();

  for (auto& entity : entities)
  {
    if (entity->transform)
    {
      if (entity->transform->position.x < 0 ||
          entity->transform->position.x > m_config.window.width)
      {
        entity->transform->velocity.x = -(entity->transform->velocity.x);
      }

      if (entity->transform->position.y < 0 ||
          entity->transform->position.y > m_config.window.height)
      {
        entity->transform->velocity.y = -(entity->transform->velocity.y);
      }

      entity->transform->position += entity->transform->velocity;
    }
  }
}

void Game::systemPlayer()
{
  if (!m_player)
  {
    return;
  }

  if (m_player->transform && m_player->input)
  {
    Vec2 playerDirection;

    if (m_player->input->up)
      playerDirection.y = -1;
    if (m_player->input->down)
      playerDirection.y = +1;
    if (m_player->input->left)
      playerDirection.x = -1;
    if (m_player->input->right)
      playerDirection.x = +1;
    if (m_player->input->shoot)
      spawnBullet();

    m_player->transform->velocity = playerDirection * m_config.player.speed;
    m_player->transform->angle += 5.f;
  }
}

void Game::systemEnemies()
{
  m_enemyTimer++;
  if (m_enemyTimer >= m_config.enemy.spawnInterval)
  {
    m_enemyTimer = 0;
    spawnEnemy();
  }
}

void Game::systemInput()
{
  clearInputs();

  EntitiesVector entities = m_manager.getEntities();

  for (auto &entity: entities)
  {
    if (entity->input)
    {
      if (IsKeyDown(KEY_W))
        entity->input->up = true;
      if (IsKeyDown(KEY_S))
        entity->input->down = true;
      if (IsKeyDown(KEY_A))
        entity->input->left = true;
      if (IsKeyDown(KEY_D))
        entity->input->right = true;
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        entity->input->shoot = true;
      if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        entity->input->specialWeapon = true;

      entity->input->shootTarget = Vec2(
        static_cast<float>(GetMouseX()),
        static_cast<float>(GetMouseY())
      );
      entity->input->specialWeaponTarget = Vec2(
        static_cast<float>(GetMouseX()),
        static_cast<float>(GetMouseY())
      );
    }
  }
}

void Game::systemCollision()
{
  EntitiesVector enemies = m_manager.getEntities("Enemy");

  if (!m_player || enemies.size() == 0)
  {
    return;
  }

  for (size_t e_idx = 0; e_idx < enemies.size(); e_idx++)
  {
    if (m_player->collision && enemies[e_idx]->collision)
    {

      float collisonDistance = 
          m_player->collision->radius + enemies[e_idx]->collision->radius;
      float entitiesDistance =
          m_player->transform->position.distance(enemies[e_idx]->transform->position);

      if (entitiesDistance <= collisonDistance)
      {
        enemies[e_idx]->destroy();
        killPlayer(); 
      }
    }
  }
}


void Game::systemBullets()
{
  EntitiesVector bullets = m_manager.getEntities("Bullet");
  EntitiesVector enemies = m_manager.getEntities("Enemy");

  if (bullets.size() == 0 || enemies.size() == 0)
    return;

  for (auto &bullet: bullets)
  {
    for (auto &enemy: enemies)
    {
      if (!(bullet->collision) || !(enemy->collision))
        continue;
      
      if (checkCollision(bullet, enemy))
      {
        m_score += enemy->score->score;

        killBullet(bullet);
        killEnemy(enemy);
      }
      
    }
  }
}

void Game::systemTimer()
{
  EntitiesVector entities = m_manager.getEntities();

  for (auto &entity: entities)
  {
    if (!(entity->timer))
      continue;

    if (entity->timer->currentCount == 0)
      //
      // XXX: Не гибкое решение. Нету возможности вызывать свой код обработки
      // смерти сущности.
      //
      entity->destroy();
    else 
      entity->timer->currentCount--;

    if (!(entity->shape))
      continue;

    float alphaNormilized = 
      static_cast<float>(entity->timer->currentCount) / 
      static_cast<float>(entity->timer->totalCount);

    // 
    // XXX: Каким-то образом текущее значение таймера оказалось больше, чем
    // его значение при инициализации. Это может привести к переполнению
    // значению альфа канала цвета, т.к. множитель альфа-канала не
    // нормализуется корректно.
    //
    if (entity->timer->currentCount > entity->timer->totalCount)
      std::cerr << "Timer value greater than it should be ("
                << entity->timer->currentCount << "/"
                << entity->timer->totalCount << ")" << std::endl;

    entity->shape->fill.a = static_cast<uint8_t>(alphaNormilized * 255);

  }
}

void Game::systemSpecialWeapon()
{
  m_specialWeaponTimer++;
  const int specialWeaponTimeout = 120;

  if (m_player->input->specialWeapon)
  {
    if (m_specialWeaponTimer >= specialWeaponTimeout)
    {
      m_specialWeaponTimer = 0;
      spawnGranade();
    }
    else
    {
      std::cout << "Granade timeout" << std::endl;
    }
  }
}
/******************************************************************************
 * KILL 
 *****************************************************************************/

void Game::killPlayer()
{
  if (!m_player)
    return;

  if (m_player->transform)
  {
    m_player->transform->position.x = 
      static_cast<float>(m_config.window.width / 2);
    m_player->transform->position.y = 
      static_cast<float>(m_config.window.height / 2);
  }
  else
  {
    std::cerr << "Player doesn't have \"Transform\" component."
              << "That strange."
              << std::endl;
  }
}

void Game::killEnemy(std::shared_ptr<Entity> enemy)
{
  if (!enemy)
    return;

  float angleStep = DEG2RAD * 360.f / enemy->shape->numberVerticies;

  // Spawning particles
  for (size_t i = 0; i < enemy->shape->numberVerticies; ++i)
  {
    auto particle = m_manager.addEntity("Particle");

    particle->transform = std::make_shared<CTransform>(
        enemy->transform->position,
        Vec2(sinf(i * angleStep), cosf(i * angleStep)),
        0.f);

    particle->shape = std::make_shared<CShape>(
        enemy->shape->numberVerticies,
        enemy->shape->outline,
        enemy->shape->fill,
        enemy->shape->thickness / 3.f,
        enemy->shape->radius / 3.f);

    particle->timer = std::make_shared<CTimer>(m_config.enemy.particleLifetime);
      
  }

  enemy->destroy();

}

void Game::killBullet(std::shared_ptr<Entity> bullet)
{
  if (!bullet)
    return;

  bullet->destroy();
}


/******************************************************************************
 * UTILITY
 *****************************************************************************/
bool Game::readConfigFile(const std::string& pathToConfigFile)
{
  std::ifstream configFile(m_currentWorkingDirectory + pathToConfigFile);
  if (!configFile)
  {
    std::cerr << "Failed to open file: " << m_currentWorkingDirectory + pathToConfigFile << std::endl;
    return false;
  }

  std::string identifier;
  while (configFile >> identifier)
  {
    if (identifier == "Window")
    {
      configFile >> m_config.window.width;
      configFile >> m_config.window.height;
      configFile >> m_config.window.FPSLimit;
      configFile >> m_config.window.isFullScreen;
    }
    else if (identifier == "Font")
    {
      int r, g, b;
      configFile >> m_config.font.name;
      configFile >> m_config.font.size;
      configFile >> r >> g >> b;

      m_config.font.color.r = r;
      m_config.font.color.g = g;
      m_config.font.color.b = b;
      m_config.font.color.a = 255;
    }
    else if (identifier == "Player")
    {
      int r, g, b;

      configFile >> m_config.player.shapeRadius;
      configFile >> m_config.player.collisionRadius;
      configFile >> m_config.player.speed;
      configFile >> r >> g >> b;

      m_config.player.fillColor.r = r;
      m_config.player.fillColor.g = g;
      m_config.player.fillColor.b = b;
      m_config.player.fillColor.a = 255;

      configFile >> r >> g >> b;

      m_config.player.outlineColor.r = r;
      m_config.player.outlineColor.g = g;
      m_config.player.outlineColor.b = b;
      m_config.player.outlineColor.a = 255;

      configFile >> m_config.player.thickness;
      configFile >> m_config.player.sidesNumber;
    }
    else if (identifier == "Enemy")
    {
      int r, g, b;

      configFile >> m_config.enemy.shapeRadius;
      configFile >> m_config.enemy.collisionRadius;
      configFile >> m_config.enemy.minSpeed;
      configFile >> m_config.enemy.maxSpeed;
      configFile >> r >> g >> b;

      m_config.enemy.outlineColor.r = r;
      m_config.enemy.outlineColor.g = g;
      m_config.enemy.outlineColor.b = b;
      m_config.enemy.outlineColor.a = 255;

      configFile >> m_config.enemy.outlineThickness;
      configFile >> m_config.enemy.minSidesNumber;
      configFile >> m_config.enemy.maxSidesNumber;
      configFile >> m_config.enemy.particleLifetime;
      configFile >> m_config.enemy.spawnInterval;
    }
    else if (identifier == "Bullet")
    {
      int r, g, b;

      configFile >> m_config.bullet.shapeRadius;
      configFile >> m_config.bullet.collisionRadius;
      configFile >> m_config.bullet.speed;
      configFile >> r >> g >> b;

      m_config.bullet.fillColor.r = r;
      m_config.bullet.fillColor.g = g;
      m_config.bullet.fillColor.b = b;
      m_config.bullet.fillColor.a = 255;

      configFile >> r >> g >> b;

      m_config.bullet.outlineColor.r = r;
      m_config.bullet.outlineColor.g = g;
      m_config.bullet.outlineColor.b = b;
      m_config.bullet.outlineColor.a = 255;

      configFile >> m_config.bullet.sidesNumber;
      configFile >> m_config.bullet.bulletLifetime;
    }
  }

  return true;
}




void Game::drawBackground()
{
  int blockSize = 50;
  bool Switch = false;

  Color primaryColor{0x52, 0x61, 0x6B, 0xFF}; // #52616b
  Color secondaryColor{0x1E, 0x20, 0x22, 0xFF }; // #1e2022

  for (int y = 0; y < m_config.window.height; y += blockSize)
  {
    for (int x = 0; x < m_config.window.width; x += blockSize)
    {
      if (Switch)
        DrawRectangle(x, y, blockSize, blockSize, primaryColor);
      else
        DrawRectangle(x, y, blockSize, blockSize, secondaryColor);

      Switch = !Switch;
    }

    Switch = !Switch;
  }
}

void Game::drawScore()
{
  std::string scorePointsText = "Score: " + std::to_string(m_score);
  DrawTextEx(
      m_font,
      scorePointsText.c_str(),
      Vector2{0, 0},
      static_cast<float>(m_config.font.size),
      1.f,
      m_config.font.color);
}

void Game::drawPlayerPosition()
{
  std::string posText = "Pos: " + std::to_string(m_player->transform->position.x) 
                          + " " + std::to_string(m_player->transform->position.y);

  DrawTextEx(
      m_font,
      posText.c_str(),
      Vector2{0, static_cast<float>(m_config.font.size + 5)},
      static_cast<float>(m_config.font.size),
      1.f,
      m_config.font.color);
}

void Game::clearInputs()
{
   EntitiesVector entities = m_manager.getEntities();

  for (auto &entity: entities)
  {
    if (entity->input)
    {
      //
      // XXX: Обнуляет все поля компонента ввода. Возможно требуется 
      // переработатькомпонент ввода, т.к. если в дальнейшем понадобиться его 
      // расширять сюда надо будет добавлять обнуление каждого добавленного  
      // поля компонента.
      // 
      entity->input->up = false;
      entity->input->down = false;
      entity->input->left = false;
      entity->input->right = false;
      entity->input->shoot = false;
      entity->input->specialWeapon = false;
    }
  }
}

bool Game::checkCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
{
  float collisonDistance = e1->collision->radius + e2->collision->radius;

  if (e1->transform->position.distance(e2->transform->position) <= collisonDistance)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int Game::rand(int min, int max)
{
  return min + (::rand() % (max - min + 1));
}

/*****************************************************************************/

Game::Game(const char* currentWorkingDirectory)
  : m_currentWorkingDirectory(currentWorkingDirectory)
{

  // CONFIG
  if (!readConfigFile(std::string("res\\config.txt")))
  {
    std::cerr << "Failed to create config" << std::endl;
  }

  // WINDOW
  InitWindow(static_cast<int>(m_config.window.width), 
             static_cast<int>(m_config.window.height), 
             "Geomentry Wars !!!");
  SetTargetFPS(static_cast<int>(m_config.window.FPSLimit));

  if (m_config.window.isFullScreen)
  {
    ToggleFullscreen();
  }

  std::string fontFileAbsolutePath = m_currentWorkingDirectory + m_config.font.name;
  m_font = LoadFontEx(fontFileAbsolutePath.c_str(), static_cast<int>(m_config.font.size), nullptr, 0);
  if (!IsFontValid(m_font))
  {
    std::cerr << "Failed to load font: " << fontFileAbsolutePath << std::endl;
  }
  
  m_isRunning = true;

  // ENTITIES
  spawnPlayer();
}

Game::~Game()
{
  CloseWindow();
}

void Game::run()
{
  while (!WindowShouldClose())
  {
    /********************************************
     * Пользовательский ввод
     ********************************************/

    if (IsKeyPressed(KEY_P))
      m_isRunning = !m_isRunning;

    systemInput();


    /********************************************
     * Обновление состояние игры 
     ********************************************/
    if (m_isRunning)
    {
      systemPlayer();
      systemEnemies();
      systemBullets();
      systemMovement();
      systemCollision();
      systemTimer();
      systemSpecialWeapon();

      m_manager.update();
    }


    /********************************************
     * Отрисовка
     ********************************************/

    BeginDrawing();

    systemRender();

    EndDrawing();
  }
}
