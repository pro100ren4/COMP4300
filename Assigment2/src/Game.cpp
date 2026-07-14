#include "Game.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include <raylib.h>

#include "Config.h"
#include "EntityManager.h"

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
      m_config.font.color
  );
}

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

int Game::rand(int min, int max)
{
  return min + (::rand() % (max - min + 1));
}

void Game::spawnPlayer()
{
  auto player = m_manager.addEntity("Player");
  player->transform = std::make_shared<CTransform>(
    Vec2(static_cast<float>(m_config.window.width / 2),
         static_cast<float>(m_config.window.height / 2)),
    Vec2(0, 0),
    0.f);
  player->shape = std::make_shared<CShape>(
    m_config.player.sidesNumber,
    m_config.player.outlineColor,
    m_config.player.fillColor,
    m_config.player.thickness,
    m_config.player.shapeRadius);

  player->collision = std::make_shared<CCollision>(m_config.player.collisionRadius);
  player->input = std::make_shared<CInput>();
}

void Game::spawnEnemy()
{
  Color enemyColors[] = {
    RED,
    GREEN,
    BLUE,
    WHITE,
    GRAY,
    BLACK
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

  Color enemyColor = enemyColors[enemyNumberSides % 6];

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

void Game::systemRender()
{
  drawBackground();

  EntitiesVector entities = m_manager.getEntities();

  for (auto& entity : entities)
  {
    if (entity->shape && entity->transform)
    {
      Vector2 temp = {};
      temp.x = entity->transform->position.x;
      temp.y = entity->transform->position.y;
      DrawPoly(
        temp,
        static_cast<int>(entity->shape->numberVerticies),
        entity->shape->radius,
        entity->transform->angle,
        entity->shape->fill);
      DrawPolyLinesEx(
        temp,
        static_cast<int>(entity->shape->numberVerticies),
        entity->shape->radius,
        entity->transform->angle,
        entity->shape->thickness,
        entity->shape->outline);
    }

    if (entity->input)
    {
      float x = entity->input->shootTarget.x;
      float y = entity->input->shootTarget.y;
      DrawRectangle(x - 5, y - 5, 10, 10, WHITE);
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

void Game::systemCollision()
{
  EntitiesVector players = m_manager.getEntities("Player");
  EntitiesVector enemies = m_manager.getEntities("Enemy");

  for (auto &player: players)
  {
    for (auto &enemy: enemies)
    {
      if (player->collision && enemy->collision)
      {
        if (checkCollision(player, enemy))
        {
          // FIXME: Почему-то при смерти игрок умирает бесконечно. Возможно
          // тут произошла инвалидация итераторов и програма начала чудить.
          // Необходимо отдельно протестировать менеджер сущьностей на
          // вшивость.
          std::cout << "DIE player: " << player << " enemy: " << enemy << std::endl;
          player->destroy();
          enemy->destroy();
          // spawnPlayer();
        }
      }
    }
  }
}

void Game::spawnBullet() {
  std::cout << "SHOOOT" << std::endl;
}

void Game::systemPlayer()
{
  EntitiesVector players = m_manager.getEntities("Player");

  for (auto& player : players)
  {
    if (player->transform && player->input)
    {
      Vec2 playerDirection;

      if (player->input->up)
        playerDirection.y = -1;
      if (player->input->down)
        playerDirection.y = +1;
      if (player->input->left)
        playerDirection.x = -1;
      if (player->input->right)
        playerDirection.x = +1;
      if (player->input->shoot)
        spawnBullet();

      player->transform->velocity = playerDirection * m_config.player.speed;
      player->transform->angle += 5.f;
    }
  }

  EntitiesVector entities = m_manager.getEntities("Player");

  for (auto& entity : entities)
  {
    if (entity->input && entity->transform)
    {
      Vector2 playerDireciton = {};
    }
  }
}

void Game::clearInputs()
{
   EntitiesVector entities = m_manager.getEntities();

  for (auto &entity: entities)
  {
    if (entity->input)
    {
      // XXX: Обнуляет все поля компонента ввода. Возможно требуется 
      // переработатькомпонент ввода, т.к. если в дальнейшем понадобиться его 
      // расширять сюда надо будет добавлять обнуление каждого добавленного  
      // поля компонента.
      entity->input->up = false;
      entity->input->down = false;
      entity->input->left = false;
      entity->input->right = false;
      entity->input->shoot = false;
    }
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

      entity->input->shootTarget = Vec2(
        static_cast<float>(GetMouseX()),
        static_cast<float>(GetMouseY())
      );
    }
  }
}

Game::Game(const char* currentWorkingDirectory)
  : m_currentWorkingDirectory(currentWorkingDirectory)
{

  if (!readConfigFile(std::string("res\\config.txt")))
  {
    std::cerr << "Failed to create config" << std::endl;
  }

  // WINDOW
  InitWindow(m_config.window.width, 
             m_config.window.height, 
             "Geomentry Wars !!!");
  SetTargetFPS(static_cast<int>(m_config.window.FPSLimit));

  if (m_config.window.isFullScreen)
  {
    ToggleFullscreen();
  }

  std::string fontFileAbsolutePath = m_currentWorkingDirectory + m_config.font.name;
  m_font = LoadFontEx(fontFileAbsolutePath.c_str(), m_config.font.size, nullptr, 0);
  if (!IsFontValid(m_font))
  {
    std::cerr << "Failed to load font: " << fontFileAbsolutePath << std::endl;
  }

  // ENTITIES
  spawnPlayer();
  m_manager.update();
}

Game::~Game()
{
  CloseWindow();
}

void Game::destroyPlayer() {}

void Game::destroyEnemy() {}

void Game::run()
{
  while (!WindowShouldClose())
  {
    /* INPUT */

    systemInput();


    /* UPDATE STATE */

    m_enemyTimer++;
    if (m_enemyTimer >= m_config.enemy.spawnInterval)
    {
      m_enemyTimer = 0;
      m_score++;
      spawnEnemy();
    }

    systemPlayer();
    systemMovement();
    systemCollision();

    m_manager.update();


    /* RENDERING */

    BeginDrawing();

    systemRender();

    EndDrawing();
  }
}
