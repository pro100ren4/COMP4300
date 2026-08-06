#pragma once

#include <memory>

#include "Config.h"
#include "EntityManager.h"
#include "Scene.h"

class SceneLevel : public Scene
{
  EntityManager m_entities;
  std::shared_ptr<LevelConfig> m_levelConfig;
  std::shared_ptr<Entity> m_player;

  bool m_displaySprites = true;
  bool m_displayGrid = false;
  bool m_displayAABB = false;

  const int m_tileWidth = 18;
  const int m_tileHeight = 18;

  float m_gravity = 0.f;

  void createTile(const TileConfig &c);
  void createDecoration(const DecConfig &c);
  void createPlayer(const PlayerConfig &c);

  void drawEntities();
  void DEBUG_drawGrid();
  void DEBUG_drawAABB();
  void DEBUG_drawInfo();

  Vector2 getOverlap(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
  Vector2 getPrevOverlap(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);

  void systemAnimation();
  void systemPhysics();
  void systemMovement();

public:
  SceneLevel(std::shared_ptr<LevelConfig> levelConfig);
  ~SceneLevel();

  void systemInput()  override;
  void systemUpdate() override;
  void systemRender() override;
};
